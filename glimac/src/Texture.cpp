#include "Texture.hpp"

Texture::Texture(GLenum target)
  : target(target)
{
  glGenTextures(1, &id);
}

Texture::~Texture()
{
  glDeleteTextures(1, &id);
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
      break;
    default: //Implementer les autres types de texture
      break;
  }
  unbind();
}


