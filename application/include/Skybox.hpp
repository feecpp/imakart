#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <string>
#include "Vertex3D.hpp"
#include "ShaderProgram.hpp"
#include "CubeMapTexture.hpp"
#include "Camera.hpp"
#include "VBO.hpp"
#include "VAO.hpp"


class Skybox{
public:
	Skybox();

	~Skybox();

  void setCamera(const Camera* pCamera){
    m_pCamera = pCamera;
  }
    
  bool init(const std::string& Directory,
            const std::string& PosXFilename,
            const std::string& NegXFilename,
            const std::string& PosYFilename,
            const std::string& NegYFilename,
            const std::string& PosZFilename,
            const std::string& NegZFilename);
    
  void render(const glimac::ShaderProgram& shaderProgram) const;

  void createVertex();

  void setVBO();

  void setVAO();

private:
  const GLsizeiptr verticesSize() const
    {return 36 * sizeof(glimac::Vertex3D);}

	const Camera* m_pCamera;
  glimac::CubemapTexture* m_pCubemapTex;

  glimac::Vertex3DSimple vertices[24]; // triangle Fan

  glimac::LowLevelVBO vbo;
  glimac::VAO vao;
  
};

#endif
