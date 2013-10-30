#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <Shader.hpp>
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

  ShaderProgram(ShaderProgram&& rvalue): programId(rvalue.programId) {
    rvalue.programId = 0;
    for (size_t i = 0; i < rvalue.shadersList.size(); ++i)
    {
      shadersList.push_back(rvalue.shadersList[i]);
      rvalue.shadersList[i] = nullptr;
    }
  }

  ShaderProgram& operator =(ShaderProgram&& rvalue) {
    programId = rvalue.programId;
    rvalue.programId = 0;
    for (size_t i = 0; i < rvalue.shadersList.size(); ++i)
    {
      shadersList.push_back(rvalue.shadersList[i]);
      rvalue.shadersList[i] = nullptr;
    }
    return *this;
  }

  //Méthode utilitaire
  static ShaderProgram loadProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
  void addShader(GLenum shaderType, const std::string& shaderFilePath);
  bool compileAndLinkShaders(std::string& logInfo) const;
  void use() const;

  GLint getUniformIndex(const std::string& uniformName);
  void setUniform(GLint uniformIndex, const glm::mat3& matrix);
  void setUniform(GLint uniformIndex, const glm::mat4& matrix);

  GLint getId() const
    {return programId;}

private:
  ShaderProgram(const ShaderProgram&);
  ShaderProgram& operator =(const ShaderProgram&);

  GLuint programId;
  std::vector<Shader* > shadersList;
};

}//namespace glimac

#endif // SHADERPROGRAM_HPP
