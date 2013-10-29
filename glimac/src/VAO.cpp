#include "VAO.hpp"
#include "VBO.hpp"
#include <iostream>
#include "OpenGLDebugger.hpp"

using namespace glimac;

VAO::VAO()
{
  glGenVertexArrays(1, &vaoId);
  //OpenGLDebugger::checkError();
}

VAO::~VAO()
{
  glDeleteVertexArrays(1, &vaoId);
  //OpenGLDebugger::checkError();
}

void VAO::bind() const
{
  glBindVertexArray(vaoId);
  //OpenGLDebugger::checkError();
}

void VAO::unbind() const
{
  glBindVertexArray(0);
}

GLuint VAO::getId() const{
	return vaoId;
}

void VAO::enableVertexAttribArray(GLuint index)
{
  bind();
  glEnableVertexAttribArray(index);
  unbind();
  //OpenGLDebugger::checkError();
}

void VAO::disableVertexAttribArray(GLuint index)
{
  bind();
  glDisableVertexAttribArray(index);
  unbind();
  //OpenGLDebugger::checkError();
}

void VAO::vertexAttribPointer(const VBO &vboToBind, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const
{
  bind();
  vboToBind.bind();
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  vboToBind.unbind();
  unbind();
  //OpenGLDebugger::checkError();
}
