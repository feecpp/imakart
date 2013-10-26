#include "VBO.hpp"
#include <iostream>
#include "OpenGLDebugger.hpp"

using namespace glimac;

LowLevelVBO::LowLevelVBO(GLenum target)
  : target(target){
	glGenBuffers(1, &vboId);
}

LowLevelVBO::LowLevelVBO(const GLvoid* data, GLsizeiptr dataSizeInBytes, GLenum usage, GLenum target)
  : target(target){
  glGenBuffers(1, &vboId);
  bind();
  glBufferData(target, dataSizeInBytes, data, usage);
  unbind();
  OpenGLDebugger::checkError();
}

LowLevelVBO::~LowLevelVBO()
{
  std::cout << "Deleting LowLevelVBO " << vboId << std::endl;
  glDeleteBuffers(1, &vboId);
  OpenGLDebugger::checkError();
}

void LowLevelVBO::setBufferData(const GLvoid* data, GLsizeiptr dataSizeInBytes, GLenum usage){
  bind();
  glBufferData(target, dataSizeInBytes, data, usage);
  unbind();
  OpenGLDebugger::checkError();
}

void LowLevelVBO::bind() const
{
  glBindBuffer(target, vboId);
}

void LowLevelVBO::unbind() const
{
  glBindBuffer(target, 0);
}
