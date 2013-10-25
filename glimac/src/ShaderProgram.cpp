#include <ShaderProgram.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

using namespace glimac;

ShaderProgram::ShaderProgram()
{
  programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
  //Properly delete shaders hosted
  std::vector<Shader* >::iterator currentShader;
  for (currentShader = shadersList.begin(); currentShader != shadersList.end(); ++currentShader)
    delete *currentShader;

  glDeleteProgram(programId);
}

void ShaderProgram::addShader(GLenum shaderType, const std::string& shaderSource)
{
  Shader* newShader = new Shader(shaderType, shaderSource);
  shadersList.push_back(newShader);
}

bool ShaderProgram::compileAndLinkShaders(std::string &logInfo) const
{
  std::vector<Shader* >::const_iterator currentShader;
  for (currentShader = shadersList.begin(); currentShader != shadersList.end(); ++currentShader)
  {
    if (!(*currentShader)->compile(logInfo))
      return false;
    glAttachShader(programId, (*currentShader)->getId());
  }

  glLinkProgram(programId);

  GLint linkStatus;
  glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
  if(linkStatus == GL_FALSE) {
    GLint logLength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

    char log[logLength];

    glGetProgramInfoLog(programId, logLength, 0, log);
    logInfo.append(log);
    return false;
  }
  for (currentShader  = shadersList.begin(); currentShader
      != shadersList.end(); ++currentShader)
    glDetachShader(programId, (*currentShader)->getId());
  return true;
}

void ShaderProgram::useProgram() const
{
  glUseProgram(programId);
}

GLint ShaderProgram::getUniformIndex(const std::string &uniformName)
{
  return glGetUniformLocation(programId, uniformName.c_str());
}

void ShaderProgram::setUniform(GLint uniformIndex, const glm::mat3 &matrix)
{
  glUniformMatrix3fv(uniformIndex, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(GLint uniformIndex, const glm::mat4& matrix)
{
  glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, glm::value_ptr(matrix));
}
