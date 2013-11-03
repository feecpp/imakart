#include "VBO.hpp"
#include <iostream>
#include "OpenGLDebugger.hpp"

using namespace glimac;

LowLevelVBO::LowLevelVBO(GLenum target)
  : target(target){
	glGenBuffers(1, &vboId);
  std::cout << "LowLevelVBO id" << vboId << " créé" << std::endl;
}

LowLevelVBO::LowLevelVBO(const GLvoid* data, GLsizeiptr dataSizeInBytes, GLenum usage, GLenum target)
  : target(target){
  glGenBuffers(1, &vboId);
  bind();
  glBufferData(target, dataSizeInBytes, data, usage);
  unbind();
  std::cout << "LowLevelVBO id" << vboId << " détruit" << std::endl;
  //OpenGLDebugger::checkError();
}

LowLevelVBO::~LowLevelVBO()
{
  glDeleteBuffers(1, &vboId);
  std::cout << "LowLevelVBO id" << vboId << " détruit" << std::endl;
  //OpenGLDebugger::checkError();
}

void LowLevelVBO::setBufferData(const GLvoid* data, GLsizeiptr dataSizeInBytes, GLenum usage){
  bind();
  glBufferData(target, dataSizeInBytes, data, usage);
  unbind();
  //OpenGLDebugger::checkError();
}

void LowLevelVBO::bind() const
{
  glBindBuffer(target, vboId);
}

void LowLevelVBO::unbind() const
{
  glBindBuffer(target, 0);
}
