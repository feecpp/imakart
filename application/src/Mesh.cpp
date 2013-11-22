#include "Mesh.hpp"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <string>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::draw(const glimac::ShaderProgram& shaderProgram) const
{
  GLint modelIndex = shaderProgram.getUniformIndex("model");
  shaderProgram.setUniform(modelIndex, glm::scale(glm::mat4(1.f), glm::vec3(0.5f)));
  meshVAO.bind();
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
  meshVAO.unbind();
}

void Mesh::update()
{

}

void Mesh::loadFromFile(const std::string& filePath)
{
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile( filePath,
         aiProcess_PreTransformVertices     |
         aiProcess_Triangulate              |
         aiProcess_JoinIdenticalVertices    |
         aiProcess_SortByPType);

  if (!scene)
  {
    std::cerr << "Impossible de trouver le fichier de modele 3D : " << filePath << "." << std::endl;
    throw std::runtime_error("Fichier 3D introuvable");
  }

  aiNode* rootNode = scene->mRootNode;


  //Normalement l'option de PostProcessing devrait faire qu'on a qu'un seul mesh...(à vérifier)
  assert(rootNode->mNumMeshes == 1);
  aiMesh* mesh = scene->mMeshes[0];

   //On charge la position des vertices (charger tous les attributs plus tard)
  std::vector<aiVector3D> vertices;
  vertices.reserve(mesh->mNumVertices);

  for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
  {
    vertices.push_back(mesh->mVertices[j]);
  }
  //On charge les indices pour dessiner
  for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
  {
    const aiFace& face = mesh->mFaces[j];
    assert(face.mNumIndices == 3);
    indices.push_back(face.mIndices[0]);
    indices.push_back(face.mIndices[1]);
    indices.push_back(face.mIndices[2]);
  }

  numVertices = vertices.size();

  meshVBO.setBufferData((const GLvoid*) &vertices[0], numVertices * sizeof(aiVector3D), GL_STATIC_DRAW);
  meshVAO.vertexAttribPointer(meshVBO, 0, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) 0);
  meshVAO.enableVertexAttribArray(0);
}
