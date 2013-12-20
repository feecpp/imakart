#ifndef MESH_HPP
#define MESH_HPP

#include "Object3D.hpp"
#include <VBO.hpp>
#include <VAO.hpp>
#include <vector>
#include <glm/glm.hpp>

/**
 * @brief The Mesh class represente un objet 3D modelise et non anime.
 * Le mesh est charge dans un unique VBO avant d'etre envoye a la carte graphique,
 * aucune notion de graphe de scene n'est prise en compte par cette classe.
 */
class Mesh : public Object3D
{
public:
  struct Material
  {
    glm::vec4 ambientColor;
    glm::vec4 diffuseColor;
    glm::vec4 specularColor;
    float shininess;
  };

  Mesh();
  virtual ~Mesh();

  virtual void draw(const glimac::ShaderProgram& shaderProgram, const glm::mat4 viewMatrix) const;
  virtual void update();

  /**
   * @brief loadFromFile charge un fichier 3D dans le Mesh et l'envoie directement
   * a la carte graphique.
   * Accepte tous les formats geres par assimp.
   * @param filePath chemin d'accÃ¨s au fichier (relatif Ã  l'emplacement
   * de l'executable)
   */
  void loadFromFile(const std::string& filePath);

private:
  /* ImplÃ©mentation basique :
   * pour un VBO Ã  l'indice 'i' correspond un VAO et un material Ã  l'indice 'i'.
   * A voir plus tard si faut pas faire un truc plus proche, pour l'instant je me suis
   * concentrÃ© sur le rÃ©sultat...
   * Utilisation des pointeurs parce que l'allocation des VBO/VAO est chiante
   * Ã  gÃ©rer.
   */
  std::vector<glimac::LowLevelVBO* > meshVBOs;
  std::vector<glimac::VAO *> meshVAOs;
  std::vector<Material> materials;

  std::vector<std::vector<unsigned int>> indices;
  glm::mat4 modelMatrix;

};

#endif // MESH_HPP
