#ifndef MESH_HPP
#define MESH_HPP

#include "Object3D.hpp"
#include <VBO.hpp>
#include <VAO.hpp>

class Mesh : public Object3D
{
public:
  Mesh();
  virtual ~Mesh();

  virtual void draw(const glimac::ShaderProgram& shaderProgram) const;
  virtual void update();

  /**
   * @brief loadFromFile charge un fichier 3D dans le Mesh. Le mesh
   * représente maintenant le modèle dessiné dans le fichier 3D. Accepte
   * tous les formats gérés par assimp.
   * @param filePath chemin d'accès au fichier (relatif à l'emplacement
   * de l'executable)
   */
  void loadFromFile(const std::string& filePath);

private:
  glimac::LowLevelVBO meshVBO;
  glimac::VAO meshVAO;
  size_t numVertices;

};

#endif // MESH_HPP
