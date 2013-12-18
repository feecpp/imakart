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
  /**
   * @brief loadProgram créé un ShaderProgram constitué des deux shaders décrits par les fichiers
   * dont le chemin d'accès est spécifié en paramètre.
   * Attention : cette méthode propage une std::runtime_error si un ou les fichiers n'existent pas.
   * @param vertexShaderFilePath
   * @param fragmentShaderFilePath
   * @return le ShaderProgram contenant les deux shaders
   */
  static ShaderProgram loadProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

  /**
   * @brief addShader ajoute un shader décrit par le fichier dont le chemin d'accès est
   * spécifié en paramètre.
   * Attention : cette méthode propage une std::runtime_error si un ou les fichiers n'existent pas.
   *au ShaderProgram.
   * @param shaderType
   * @param shaderFilePath
   */
  void addShader(GLenum shaderType, const std::string& shaderFilePath);
  bool compileAndLinkShaders(std::string& logInfo) const;
  void use() const;

  GLint getUniformIndex(const std::string& uniformName) const;

  /**
   * @brief setUniform
   * @param uniformIndex l'index de l'uniform obtenu par la méthode
   * getUniformIndex(uniformName)
   * @param matrix
   * @see getUniformIndex(const std::string& uniformName)
   */
  void setUniform(GLint uniformIndex, const glm::mat3& matrix) const;
  void setUniform(GLint uniformIndex, const glm::mat4& matrix) const;
  void setUniform(GLint uniformIndex, const glm::vec4& vector) const;
  void setUniform(GLint uniformIndex, const glm::vec3& vector) const;
  void setUniform(GLint uniformIndex, int a, const glm::vec3& vector) const;
  void setUniform(GLint uniformIndex, float scalar) const;
  void setUniform(GLint uniformIndex, int scalar) const;

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
