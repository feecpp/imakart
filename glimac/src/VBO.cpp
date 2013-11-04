#include "VBO.hpp"

#if DEBUG
  #include <iostream>
  #include "OpenGLDebugger.hpp"
#endif

using namespace glimac;

LowLevelVBO::LowLevelVBO(GLenum target)
  : target(target){
	glGenBuffers(1, &vboId);
#if DEBUG
  std::cout << "LowLevelVBO id" << vboId << " créé" << std::endl;
#endif
}

LowLevelVBO::LowLevelVBO(const GLvoid* data, GLsizeiptr dataSizeInBytes, GLenum usage, GLenum target)
  : target(target){
  glGenBuffers(1, &vboId);
  bind();
  glBufferData(target, dataSizeInBytes, data, usage);
  unbind();
#if DEBUG
  std::cout << "LowLevelVBO id" << vboId << " détruit" << std::endl;
  OpenGLDebugger::checkError();
#endif
}

LowLevelVBO::~LowLevelVBO()
{
  glDeleteBuffers(1, &vboId);
#if DEBUG
  std::cout << "LowLevelVBO id" << vboId << " détruit" << std::endl;
  OpenGLDebugger::checkError();
#endif
}

void LowLevelVBO::setBufferData(const GLvoid* data, GLsizeiptr dataSizeInBytes, GLenum usage){
  bind();
  glBufferData(target, dataSizeInBytes, data, usage);
  unbind();
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

void LowLevelVBO::bind() const
{
  glBindBuffer(target, vboId);
}

void LowLevelVBO::unbind() const
{
  glBindBuffer(target, 0);
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}
