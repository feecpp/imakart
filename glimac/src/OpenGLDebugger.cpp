#include "OpenGLDebugger.hpp"
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

void OpenGLDebugger::checkError()
{
  GLenum lastError = glGetError();

  if (lastError != GL_NO_ERROR)
    std::cerr << "OpenGL Debugger Info : ";

  switch (lastError)
  {
  case GL_NO_ERROR :
    //std::cerr << "No Error." << std::endl;
    break;
  case GL_INVALID_ENUM :
    std::cerr << "Invalid Enum." << std::endl;
    break;
  case GL_INVALID_VALUE :
    std::cerr << "Invalid value." << std::endl;
    break;
  case GL_INVALID_OPERATION :
    std::cerr << "Invalid operation." << std::endl;
    break;
  case GL_INVALID_FRAMEBUFFER_OPERATION :
    std::cerr << "Invalid Framebuffer Operation." << std::endl;
    break;
  case GL_OUT_OF_MEMORY :
    std::cerr << "Out of memory." << std::endl;
    break;
  case GL_STACK_UNDERFLOW :
    std::cerr << "Stack underflow." << std::endl;
    break;
  case GL_STACK_OVERFLOW :
    std::cerr << "Stack overflow." << std::endl;
    break;

  }
}
