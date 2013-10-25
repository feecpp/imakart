#ifndef VERTEX2DRGB_HPP
#define VERTEX2DRGB_HPP

namespace glimac
{

struct Vertex2D
{
  GLfloat x, y;

  Vertex2D(GLfloat x, GLfloat y):
    x(x), y(y) {}

};

struct Vertex2DRGB
{
  GLfloat x, y;
  GLfloat r, g, b;

  Vertex2DRGB(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b):
    x(x), y(y), r(r), g(g), b(b) {
  }

};

} // namespace glimac

#endif // VERTEX2DRGB_HPP
