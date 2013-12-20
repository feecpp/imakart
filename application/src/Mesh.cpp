#include "Mesh.hpp"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>
#include <Vertex3D.hpp>
#include <cstddef>
#include <sstream>
#include "Positionable.hpp"
#include <glm/gtx/quaternion.hpp>
#include <iostream>

Mesh::Mesh()
  : modelMatrix(1.f)
{
  for (glimac::LowLevelVBO*& vbo : meshVBOs)
    vbo = nullptr;
  for (glimac::VAO*& vao : meshVAOs)
    vao = nullptr;
}

Mesh::~Mesh()
{
  for (glimac::LowLevelVBO*& vbo : meshVBOs)
    delete vbo;
  for (glimac::VAO*& vao : meshVAOs)
    delete vao;
}

void Mesh::draw(const glimac::ShaderProgram& shaderProgram) const
{
  const glm::mat4 MV = viewMatrix * modelMatrix;
  const glm::mat4& normalMatrix = glm::transpose(glm::inverse(MV));
  GLint normalId = shaderProgram.getUniformIndex("uNormal");
  shaderProgram.setUniform(normalId, normalMatrix);
  GLint modelIndex = shaderProgram.getUniformIndex("model");
  shaderProgram.setUniform(modelIndex, modelMatrix);
  GLint diffuseIndex = shaderProgram.getUniformIndex("material.diffuse");
  GLint ambientIndex = shaderProgram.getUniformIndex("material.ambient");
  GLint specularIndex = shaderProgram.getUniformIndex("material.specular");
  GLint shininessIndex = shaderProgram.getUniformIndex("material.shininess");

  for (unsigned int i = 0; i < meshVAOs.size(); ++i)
  {
    shaderProgram.setUniform(diffuseIndex, materials[i].diffuseColor);
    shaderProgram.setUniform(ambientIndex, materials[i].ambientColor);
    shaderProgram.setUniform(specularIndex, materials[i].specularColor);
    shaderProgram.setUniform(shininessIndex, materials[i].shininess);

    meshVAOs[i]->bind();
    glDrawElements(GL_TRIANGLES, indices[i].size(), GL_UNSIGNED_INT, &(indices[i][0]));
    meshVAOs[i]->unbind();
  }
}

void Mesh::update()
{
  modelMatrix = glm::mat4(1.f);
  modelMatrix = glm::toMat4(model->getOrientation()) * modelMatrix;
  modelMatrix = glm::translate(glm::mat4(1.f), model->getPosition()) * modelMatrix;
}

void Mesh::loadFromFile(const std::string& filePath)
{
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile( filePath,
         aiProcess_PreTransformVertices     |
         aiProcess_Triangulate              |
         aiProcess_JoinIdenticalVertices    |
         aiProcess_GenNormals               |
         aiProcess_OptimizeGraph            |
         aiProcess_SortByPType              );

  if (!scene)
  {
    std::ostringstream errorMessage;
    errorMessage << "Impossible de trouver le fichier de modele 3D : " << filePath << "." << std::endl;
    throw std::runtime_error(errorMessage.str());
  }


  meshVBOs.reserve(scene->mNumMeshes);
  meshVAOs.reserve(scene->mNumMeshes);
  materials.resize(scene->mNumMeshes);
  indices.resize(scene->mNumMeshes);

  //On les rÃ©utilise Ã  chaque fois pour optim
  aiColor3D ambient;
  aiColor3D diffuse;
  aiColor3D specular;
  float shininess;
  for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
  {
    const aiMesh* const mesh = scene->mMeshes[i];
    const aiMaterial* const material = scene->mMaterials[mesh->mMaterialIndex];
    material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
    material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
    material->Get(AI_MATKEY_SHININESS, shininess);
    materials[i].ambientColor.r = ambient.r; materials[i].ambientColor.g = ambient.g;
    materials[i].ambientColor.b = ambient.b; materials[i].ambientColor.a = 1.f;
    materials[i].diffuseColor.r = diffuse.r; materials[i].diffuseColor.g = diffuse.g;
    materials[i].diffuseColor.b = diffuse.b; materials[i].diffuseColor.a = 1.f;
    materials[i].specularColor.r = specular.r; materials[i].specularColor.g = specular.g;
    materials[i].specularColor.b = specular.b; materials[i].specularColor.a =  1.f;
    materials[i].shininess = shininess;

    meshVBOs.push_back(new glimac::LowLevelVBO());
    meshVAOs.push_back(new glimac::VAO());

    std::vector<glimac::Vertex3D> vertices;
    vertices.reserve(mesh->mNumVertices);

    for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
    {
      glimac::Vertex3D current;
      current.position = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
      current.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
      current.textureCoordinates = mesh->HasTextureCoords(0) ? glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y) : glm::vec2(0.f, 0.f);
      vertices.push_back(current);
    }
    //On charge les indices pour dessiner
    for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
    {
      const aiFace& face = mesh->mFaces[j];
      for (unsigned int k = 0; k < face.mNumIndices; ++k)
      {
        indices[i].push_back(face.mIndices[k]);
      }
    }

    meshVBOs[i]->setBufferData((const GLvoid*) &vertices[0], vertices.size() * sizeof(glimac::Vertex3D), GL_STATIC_DRAW);

    meshVAOs[i]->vertexAttribPointer(*meshVBOs[i], 0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid*) offsetof(glimac::Vertex3D, position));
    meshVAOs[i]->vertexAttribPointer(*meshVBOs[i], 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid*) offsetof(glimac::Vertex3D, textureCoordinates));
    meshVAOs[i]->vertexAttribPointer(*meshVBOs[i], 2, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid*) offsetof(glimac::Vertex3D, normal));

    meshVAOs[i]->enableVertexAttribArray(0);
    meshVAOs[i]->enableVertexAttribArray(1);
    meshVAOs[i]->enableVertexAttribArray(2);

  }
}
