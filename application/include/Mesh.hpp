#ifndef MESH_HPP
#define MESH_HPP

#include "Object3D.hpp"
#include <VBO.hpp>
#include <VAO.hpp>
#include <vector>
#include <glm/glm.hpp>
#include "Texture.hpp"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure

/**
 * @brief The Mesh class represente un objet 3D modelise et non anime.
 * Le mesh est charge dans un unique VBO avant d'etre envoye a la carte graphique,
 * aucune notion de graphe de scene n'est prise en compte par cette classe.
 */
class MeshData
{
public:

  struct Material
  {
    glm::vec4 ambientColor;
    glm::vec4 diffuseColor;
    glm::vec4 specularColor;
    float shininess;
  };

  MeshData();
  virtual ~MeshData();

  virtual void draw(const glimac::ShaderProgram& shaderProgram) const;

  /**
   * @brief loadFromFile charge un fichier 3D dans le Mesh et l'envoie directement
   * a la carte graphique.
   * Accepte tous les formats geres par assimp.
   * @param filePath chemin d'accÃ¨s au fichier (relatif Ã  l'emplacement
   * de l'executable)
   */
  void loadFromFile(const std::string& filePath);

private:
  static Assimp::Importer importer;

  /* Implémentation basique :
   * pour un VBO à l'indice 'i' correspond un VAO et un material à l'indice 'i'.
   * A voir plus tard si faut pas faire un truc plus proche, pour l'instant je me suis
   * concentré sur le résultat...
   * Utilisation des pointeurs parce que l'allocation des VBO/VAO est chiante
   * à gérer.
   */
  std::vector<glimac::LowLevelVBO* > meshVBOs;
  std::vector<glimac::VAO *> meshVAOs;
  std::vector<Material> materials;
  std::vector<glimac::Texture* > textures;

  std::vector<std::vector<unsigned int>> indices;
};

class MeshDataManager
{
public:
  ~MeshDataManager();

  void preloadMesh(const std::string& filePath);
  MeshData& getMeshData(const std::string& filePath);

private:
  typedef std::pair<const std::string, MeshData* > mapPair;
  std::map<const std::string, MeshData* > data;
};

class Mesh : public Object3D
{
public:
  Mesh(MeshDataManager& dataManager, const std::string& filePath)
    : meshData(dataManager.getMeshData(filePath)), modelMatrix(1.f)
  {

  }

  virtual void draw(const glimac::ShaderProgram& shaderProgram) const
  {
    const glm::mat4 MV = viewMatrix * modelMatrix;
    const glm::mat4& normalMatrix = glm::transpose(glm::inverse(MV));
    GLint normalId = shaderProgram.getUniformIndex("uNormal");
    shaderProgram.setUniform(normalId, normalMatrix);
    GLint modelIndex = shaderProgram.getUniformIndex("model");
    shaderProgram.setUniform(modelIndex, modelMatrix);
    meshData.draw(shaderProgram);
  }

  virtual void update();

private:
  MeshData& meshData;
  glm::mat4 modelMatrix;

};

#endif // MESH_HPP
