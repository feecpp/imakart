#include <ShaderProgram.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <TextFile.hpp>
#include <stdexcept>
#include <OpenGLDebugger.hpp>

#if DEBUG
  #include <iostream>
#endif

using namespace glimac;

ShaderProgram::ShaderProgram()
{
  programId = glCreateProgram();
#if DEBUG
  std::cout << "ShaderProgram id " << programId << "créé"  << std::endl;
#endif
}

ShaderProgram::~ShaderProgram()
{
  //Properly delete shaders hosted
  std::vector<Shader* >::iterator currentShader;
  for (currentShader = shadersList.begin(); currentShader != shadersList.end(); ++currentShader)
    delete *currentShader;

  glDeleteProgram(programId);

#if DEBUG
  std::cout << "ShaderProgram id " << programId << "détruit"  << std::endl;
#endif
}

void ShaderProgram::addShader(GLenum shaderType, const std::string& shaderFilePath)
{
  std::string shaderSource;
  //RAII
  {
    glimac::TextFile shaderFile(shaderFilePath);
    if (!shaderFile.isValid())
    {
      throw std::runtime_error("Impossible de trouver : " + shaderFilePath);
    }

    shaderSource = shaderFile.getString();
  }

  Shader* newShader = new Shader(shaderType, shaderFilePath);

  newShader->setSource(shaderSource.c_str());
  shadersList.push_back(newShader);
}

bool ShaderProgram::compileAndLinkShaders(std::string &logInfo) const
{
  std::vector<Shader* >::const_iterator currentShader;
  for (currentShader = shadersList.begin(); currentShader != shadersList.end(); ++currentShader)
  {
    if (!(*currentShader)->compile(logInfo))
      return false;
    glAttachShader(programId, (*currentShader)->getGLId());
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
    glDetachShader(programId, (*currentShader)->getGLId());
  return true;
}

void ShaderProgram::use() const
{
  glUseProgram(programId);
}

GLint ShaderProgram::getUniformIndex(const std::string &uniformName) const
{
  return glGetUniformLocation(programId, uniformName.c_str());
}

void ShaderProgram::setUniform(GLint uniformIndex, const glm::mat3 &matrix) const
{
  glUniformMatrix3fv(uniformIndex, 1, GL_FALSE, glm::value_ptr(matrix));
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

void ShaderProgram::setUniform(GLint uniformIndex, const glm::mat4& matrix) const
{
  glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, glm::value_ptr(matrix));
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

void ShaderProgram::setUniform(GLint uniformIndex, const glm::vec4& vector) const
{
  glUniform4f(uniformIndex, vector.x, vector.y, vector.z, vector.w);
#if DEBUG
  OpenGLDebugger::checkError();
#endif
}

void ShaderProgram::setUniform(GLint uniformIndex, int scalar) const
{
  glUniform1i(uniformIndex,scalar);
}

ShaderProgram ShaderProgram::loadProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
  std::string vertexShaderSource;
  std::string fragmentShaderSource;
  {
    glimac::TextFile vertexShaderFile(vertexShaderFilePath);
    glimac::TextFile fragmentShaderFile(fragmentShaderFilePath);

    if (!vertexShaderFile.isValid() || !fragmentShaderFile.isValid())
    {
      throw std::runtime_error("Impossible de trouver : " + vertexShaderFilePath + "; " + fragmentShaderFilePath);
    }

    vertexShaderSource = vertexShaderFile.getString();
    fragmentShaderSource = fragmentShaderFile.getString();
  }

  ShaderProgram program;
  program.addShader(GL_VERTEX_SHADER, vertexShaderSource);
  program.addShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  return program;
}
