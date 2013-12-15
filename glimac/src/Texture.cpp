#include "Texture.hpp"

#if DEBUG
  #include <iostream>
  #include "OpenGLDebugger.hpp"
#endif

using namespace glimac;

Texture::Texture(GLenum target)
  : target(target)
{
  glGenTextures(1, &id);
  #if DEBUG
    std::cout << "Texture id " << id << " créé" << std::endl;
    OpenGLDebugger::checkError();
  #endif
}

Texture::~Texture()
{
  glDeleteTextures(1, &id);
  #if DEBUG
    std::cout << "Texture id " << id << " détruite" << std::endl;
    OpenGLDebugger::checkError();
  #endif
}


void Texture::loadTexture2D(std::string filename)
{
  sf::Image image;
  if(image.loadFromFile(filename))
  {
    setData(0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
  }
}

void Texture::bind()
{
  glBindTexture(target, id);
  binded = true;
}

void Texture::unbind()
{
  if (binded)
  {
    glBindTexture(target, 0);
    binded = false;
  }
}

bool Texture::isBinded()
{
  return binded;
}

void Texture::setData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
  bind();
  switch(target)
  {
    case GL_TEXTURE_2D:
      glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
      glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      break;
    default: //Implementer les autres types de texture
      break;
  }
  unbind();
}


