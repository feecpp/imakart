#pragma once

#include <GL/glew.h>
#include <string>

#define GLIMAC_SHADER_SRC(str) #str

namespace glimac {

class Shader {
public:
  Shader(GLenum type);

  ~Shader();

	Shader(Shader&& rvalue): m_nGLId(rvalue.m_nGLId) {
		rvalue.m_nGLId = 0;
	}

	Shader& operator =(Shader&& rvalue) {
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	GLuint getGLId() const {
		return m_nGLId;
	}

	void setSource(const char* src) {
		glShaderSource(m_nGLId, 1, &src, 0);
	}

  bool compile(std::string& logInfo);

	const std::string getInfoLog() const;

private:
	Shader(const Shader&);
	Shader& operator =(const Shader&);

	GLuint m_nGLId;
};

// Load a shader (but does not compile it)
Shader loadShader(GLenum type, const char* filename);

}
