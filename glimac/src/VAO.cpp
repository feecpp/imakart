#include "VAO.hpp"
#include "VBO.hpp"

#if DEBUG
  #include <iostream>
  #include "OpenGLDebugger.hpp"
#endif

using namespace glimac;

VAO::VAO()
{
  glGenVertexArrays(1, &vaoId);
#if DEBUG
  std::cout << "VAO id" << vaoId << " créé" << std::endl;
  OpenGLDebugger::checkError();
#endif
}

VAO::~VAO()
{
  glDeleteVertexArrays(1, &vaoId);
#if DEBUG
  std::cout << "VAO id" << vaoId << " détruit" << std::endl;
  OpenGLDebugger::checkError();
#endif
}

void VAO::bind() const
{
  glBindVertexArray(vaoId);
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

void VAO::unbind() const
{
  glBindVertexArray(0);
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

GLuint VAO::getId() const{
	return vaoId;
}

void VAO::enableVertexAttribArray(GLuint index)
{
  bind();
  glEnableVertexAttribArray(index);
  unbind();
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

void VAO::disableVertexAttribArray(GLuint index)
{
  bind();
  glDisableVertexAttribArray(index);
  unbind();
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

void VAO::vertexAttribPointer(const VBO &vboToBind, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const
{
  bind();
  vboToBind.bind();
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  vboToBind.unbind();
  unbind();
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}
