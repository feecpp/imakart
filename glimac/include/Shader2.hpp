#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

namespace glimac
{

class Shader
{
public:
  Shader(GLenum shaderType, const std::string &shaderSource);
  ~Shader();

  GLuint getId() const
    {return shaderId;}

  bool compile(std::string& logInfo) const;

private:
  //A Shader cannot be copied
  Shader(const Shader&);
  Shader& operator=(const Shader& other);

  GLuint shaderId;

};

}// namespace glimac

#endif // SHADER_HPP
