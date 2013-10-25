#ifndef VBO_HPP
#define VBO_HPP

#include <GL/glew.h>

namespace glimac
{

/**
 * @brief Interface of all VBO objects
 */
class VBO
{
public:
  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  const GLuint getId() const
    {return vboId;}


protected:
  GLuint vboId;

};

/**
 * @brief Concrete implementation of a VBO object, very close to
 * the OpenGL concrete implementation of VBOs.
 */
class LowLevelVBO : public VBO
{
public:
  LowLevelVBO(const GLvoid* data, GLsizeiptr dataSizeInBytes, GLenum usage, GLenum target = GL_ARRAY_BUFFER);
  ~LowLevelVBO();

  virtual void bind() const;
  virtual void unbind() const;

  LowLevelVBO(LowLevelVBO&& rvalue)
  {
    vboId = rvalue.vboId;
    rvalue.vboId = 0;
  }

  LowLevelVBO& operator=(LowLevelVBO&& rvalue)
  {
    vboId = rvalue.vboId;
    rvalue.vboId = 0;
    return *this;
  }

private:
  /*
   *A VBO cannot be copied
   */
  LowLevelVBO(const LowLevelVBO&);
  LowLevelVBO& operator=(const LowLevelVBO& other);

  GLenum target;
};

} // namespace glimac
#endif // VBO_HPP
