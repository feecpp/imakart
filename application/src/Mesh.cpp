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

Mesh::Mesh()
  : modelMatrix(1.f)
{

}

Mesh::~Mesh()
{

}

void Mesh::draw(const glimac::ShaderProgram& shaderProgram) const
{
  GLint modelIndex = shaderProgram.getUniformIndex("model");
  shaderProgram.setUniform(modelIndex, modelMatrix);
  GLint diffuseIndex = shaderProgram.getUniformIndex("material.diffuse");

  for (unsigned int i = 0; i < meshVAOs.size(); ++i)
  {
    shaderProgram.setUniform(diffuseIndex, materials[i].diffuseColor);
    meshVAOs[i].bind();
    glDrawElements(GL_TRIANGLES, indices[i].size(), GL_UNSIGNED_INT, &(indices[i][0]));
    meshVAOs[i].unbind();
  }
}

void Mesh::update()
{
  modelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(0.5f));
  modelMatrix = modelMatrix * glm::toMat4(model->getOrientation());
  modelMatrix = glm::translate(modelMatrix, model->getPosition());
}

void Mesh::loadFromFile(const std::string& filePath)
{
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile( filePath,
         aiProcess_PreTransformVertices     |
         aiProcess_Triangulate              |
         aiProcess_JoinIdenticalVertices    |
         aiProcess_GenNormals               |
         aiProcess_SortByPType              );

  if (!scene)
  {
    std::ostringstream errorMessage;
    errorMessage << "Impossible de trouver le fichier de modele 3D : " << filePath << "." << std::endl;
    throw std::runtime_error(errorMessage.str());
  }

  meshVBOs.resize(scene->mNumMeshes);
  meshVAOs.resize(scene->mNumMeshes);
  materials.resize(scene->mNumMeshes);
  indices.resize(scene->mNumMeshes);

  for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
  {
    aiMesh* mesh = scene->mMeshes[i];
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    aiColor4D ambient;
    aiColor4D diffuse;
    aiColor4D specular;
    material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
    material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
    materials[i].ambientColor = glm::vec4(ambient.r, ambient.g, ambient.b, ambient.a);
    materials[i].diffuseColor = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
    materials[i].specularColor = glm::vec4(specular.r, specular.g, specular.b, specular.a);

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

    meshVBOs[i].setBufferData((const GLvoid*) &vertices[0], vertices.size() * sizeof(glimac::Vertex3D), GL_STATIC_DRAW);

    meshVAOs[i].vertexAttribPointer(meshVBOs[i], 0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid*) offsetof(glimac::Vertex3D, position));
    meshVAOs[i].vertexAttribPointer(meshVBOs[i], 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid*) offsetof(glimac::Vertex3D, textureCoordinates));
    meshVAOs[i].vertexAttribPointer(meshVBOs[i], 2, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid*) offsetof(glimac::Vertex3D, normal));

    meshVAOs[i].enableVertexAttribArray(0);
    meshVAOs[i].enableVertexAttribArray(1);
    meshVAOs[i].enableVertexAttribArray(2);

  }
}
