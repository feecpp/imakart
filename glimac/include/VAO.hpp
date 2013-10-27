#ifndef VAO_HPP
#define VAO_HPP

#include <GL/glew.h>

namespace glimac
{

class VBO;

class VAO
{

public:
  VAO();
  ~VAO();

  static const GLuint MAX_VERTEX_ATTRIBUTES = GL_MAX_VERTEX_ATTRIBS;
  void bind() const;
  void unbind() const;

  GLuint getId() const;
  /*
   *These functions take care of VAO binding
   *unbinding
   **/
  void enableVertexAttribArray(GLuint index);
  void disableVertexAttribArray(GLuint index);
  void vertexAttribPointer(const VBO& vboToBind, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;

  VAO(VAO&& rvalue)
  {
    vaoId = rvalue.vaoId;
    rvalue.vaoId = 0;
  }

  VAO& operator=(VAO&& rvalue)
  {
    vaoId = rvalue.vaoId;
    rvalue.vaoId = 0;
    return *this;
  }

private:
  /*
   * A VAO cannot be copied
   */
  VAO(const VAO&);
  VAO& operator=(const VAO& other);

  GLuint vaoId;

};

} // namespace glimac

#endif // VAO_HPP
