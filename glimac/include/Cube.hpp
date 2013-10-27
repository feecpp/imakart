#ifndef CUBE_HPP
#define CUBE_HPP

#include "Vertex3D.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

namespace glimac
{

struct Cube
{

  Cube()
  {
    vertices[0].position = glm::vec3(-0.5f, -0.5f, 0.5f);
    vertices[1].position = glm::vec3(0.5f, -0.5f, 0.5f);
    vertices[2].position = glm::vec3(-0.5f, 0.5f, 0.5f);
    vertices[3].position = glm::vec3(0.5f, 0.5f, 0.5f);
    vertices[4].position = glm::vec3(-0.5f, -0.5f, -0.5f);
    vertices[5].position = glm::vec3(0.5f, -0.5f, -0.5f);
    vertices[6].position = glm::vec3(-0.5f, 0.5f, -0.5f);
    vertices[7].position = glm::vec3(0.5f, 0.5f, -0.5f);
  }

  const GLvoid* getVertices() const
    {return glm::value_ptr(vertices[0].position);}

  static const GLvoid* getIndices()
  {
    static const GLushort indices[] = {
      0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
    };
    return (const GLvoid*) indices;
  }

  static const GLsizeiptr verticesSize()
    {return 8 * sizeof(Vertex3D);}

  static const GLsizei indicesSize()
    {return GLsizei(14);}

  Vertex3D vertices[8];
};

} // namespace glimac

#endif // CUBE_HPP
