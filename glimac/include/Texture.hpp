#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/gl.h>

/**
 * @brief The Texture class
 * Implementation tres simple et bas niveau de la gestion
 * d'une texture en OpenGL. Utilise RAII pour la creation / destruction
 * de la texture sur le GPU. Ne gere pas la memoire allouee sur le CPU.
 */
class Texture
{
public:
  Texture(GLenum target);
  ~Texture();

  void bind();
  void unbind();
  bool isBinded();

  void setData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);

private:
  GLuint id;
  GLenum target;
  bool binded;
};

#endif // TEXTURE_HPP
