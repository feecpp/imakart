#include "Mesh.hpp"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <string>
#include <iostream>

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::draw(const glimac::ShaderProgram& shaderProgram) const
{
  meshVAO.bind();
  glDrawArrays(GL_TRIANGLES, 0, numVertices);
  meshVAO.unbind();
}

void Mesh::update()
{

}

void Mesh::loadFromFile(const std::string& filePath)
{
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile( filePath,
         aiProcess_CalcTangentSpace       |
         aiProcess_Triangulate            |
         aiProcess_JoinIdenticalVertices  |
         aiProcess_SortByPType);

  if (!scene) //TODO
  {
    //throw error ?
  }

  aiNode* rootNode = scene->mRootNode;
  std::cout << "Nombre de meshs: " << rootNode->mNumMeshes << std::endl;
  std::cout << "Nombre de nodes: " << rootNode->mNumChildren << std::endl;
  std::vector<aiVector3D> vertices;
  for (unsigned int i = 0; i < rootNode->mNumChildren; ++i)
  {
    aiNode* node = rootNode->mChildren[i];
    aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
    std::cout << "Num vertices: " << mesh->mNumVertices << std::endl;
    for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
    {
      vertices.push_back(mesh->mVertices[j]);
    }

  }
  numVertices = vertices.size();
  meshVBO.setBufferData((const GLvoid*) &vertices[0], numVertices * sizeof(aiVector3D), GL_STATIC_DRAW);
  meshVAO.vertexAttribPointer(meshVBO, 0, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) 0);
  meshVAO.enableVertexAttribArray(0);

}
