#ifndef VERTEX2DRGB_HPP
#define VERTEX2DRGB_HPP

#include <GL/gl.h>
#include <glm/glm.hpp>

namespace glimac
{

struct Vertex2D
{
  GLfloat x, y;

  Vertex2D(GLfloat x, GLfloat y):
    x(x), y(y) {
  }

};

struct Vertex2DRGB
{
  glm::vec2 position;
  glm::vec3 color;

  Vertex2DRGB():
	position(glm::vec2(0)), color(glm::vec3(0)){
  }
  
  Vertex2DRGB(const glm::vec2 position, const glm::vec3 color):
    position(position), color(color) {
  }
  
  Vertex2DRGB(const float x, const float y, const float r, const float g, const float b):
    position(glm::vec2(x,y)), color(glm::vec3(r,g,b)) {
  }

};

struct Vertex2DUV
{
  glm::vec2 position;
  glm::vec2 texCoord;

  Vertex2DUV():
  position(glm::vec2(0)), texCoord(glm::vec2(0)){
  }
  
  Vertex2DUV(const glm::vec2 position, const glm::vec2 texCoord):
    position(position), texCoord(texCoord) {
  }
  
  Vertex2DUV(const float x, const float y, const float u, const float v):
    position(glm::vec2(x,y)), texCoord(glm::vec2(u,v)) {
  }
};

} // namespace glimac

#endif // VERTEX2DRGB_HPP
