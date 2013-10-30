#ifndef KARTCUBE_HPP
#define KARTCUBE_HPP

#include "Object3D.hpp"
#include "Vertex3D.hpp"
#include "GL/glew.h"
#include <vector>
#include "VBO.hpp"
#include "VAO.hpp"

class KartCube : public Object3D
{
public:
  KartCube();

  /**
   * @see Object3D
   */
  virtual void draw() const;


  /**
   * @see Object3D
   */
  virtual void update();

private:
  const GLsizeiptr verticesSize() const
    {return 8 * sizeof(glimac::Vertex3D);}

  const GLsizei indicesSize() const
    {return GLsizei(14);}

  glimac::Vertex3D vertices[8];
 // const GLushort indices[14] = {0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1};

  glimac::LowLevelVBO vbo;
  glimac::VAO vao;

  glm::mat4 modelMatrix;
};

#endif // KARTCUBE_HPP
