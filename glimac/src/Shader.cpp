#include <Shader.hpp>
#include <iostream>

using namespace glimac;

Shader::Shader(GLenum shaderType, const std::string& shaderSource)
{
  shaderId = glCreateShader(shaderType);
  const char* text = shaderSource.c_str();
  const char** pText = &text;
  glShaderSource(shaderId, 1, pText, 0);
}

bool Shader::compile(std::string& logInfo) const
{
  glCompileShader(shaderId);

  GLint compileStatus;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

  GLint logLength = 0;
  glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
  char log[logLength];
  glGetShaderInfoLog(shaderId, logLength, 0, log);
  logInfo.append(log);

  if (compileStatus == GL_FALSE)
    return false;


  return true;
}

Shader::~Shader()
{
  glDeleteShader(shaderId);
}
