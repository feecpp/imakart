#ifndef MESH_HPP
#define MESH_HPP

#include "Object3D.hpp"
#include <VBO.hpp>
#include <VAO.hpp>


/**
 * @brief The Mesh class represente un objet 3D modelise et non anime.
 * Le mesh est charge dans un unique VBO avant d'etre envoye a la carte graphique,
 * aucune notion de graphe de scene n'est prise en compte par cette classe.
 */
class Mesh : public Object3D
{
public:
  Mesh();
  virtual ~Mesh();

  virtual void draw(const glimac::ShaderProgram& shaderProgram) const;
  virtual void update();

  /**
   * @brief loadFromFile charge un fichier 3D dans le Mesh et l'envoie directement
   * a la carte graphique.
   * Accepte tous les formats geres par assimp.
   * @param filePath chemin d'accès au fichier (relatif à l'emplacement
   * de l'executable)
   */
  void loadFromFile(const std::string& filePath);

private:
  glimac::LowLevelVBO meshVBO;
  glimac::VAO meshVAO;
  size_t numVertices;
  std::vector<unsigned int> indices;

};

#endif // MESH_HPP
