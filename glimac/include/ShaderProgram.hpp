#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <Shader2.hpp>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace glimac
{

class ShaderProgram
{
public:
  ShaderProgram();
  ~ShaderProgram();

  void addShader(GLenum shaderType, const std::string& shaderSource);
  bool compileAndLinkShaders(std::string& logInfo) const;
  void useProgram() const;

  GLint getUniformIndex(const std::string& uniformName);
  void setUniform(GLint uniformIndex, const glm::mat3& matrix);
  void setUniform(GLint uniformIndex, const glm::mat4& matrix);

  GLint getId() const
    {return programId;}

private:
  //A ShaderProgram cannot be copied
  ShaderProgram(const ShaderProgram&);
  ShaderProgram& operator=(const ShaderProgram& other);

  GLuint programId;
  std::vector<Shader* > shadersList;
};

}//namespace glimac

#endif // SHADERPROGRAM_HPP
