#ifndef VERTEX3D_HPP
#define VERTEX3D_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace glimac
{

struct Vertex3D
{
  glm::vec3 position;
  glm::vec2 textureCoordinates;
  glm::vec3 normal;

  Vertex3D(glm::vec3 position, glm::vec2 textureCoordinates, glm::vec3 normal)
    : position(position), textureCoordinates(textureCoordinates), normal(normal)
  {}

  explicit Vertex3D(glm::vec3 position)
    : position(position), textureCoordinates(0.f), normal(0.f)
  {}

  Vertex3D(float x, float y, float z)
    : position(glm::vec3(x, y, z)), textureCoordinates(0.f), normal(0.f)
  {}

  Vertex3D() {}
};

} //namespace glimac

#endif // VERTEX3D_HPP
