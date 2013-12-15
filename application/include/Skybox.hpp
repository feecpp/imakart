#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <string>
#include "CubeMapTexture.hpp"
#include "Camera.hpp"

class Skybox{
public:
	Skybox(const Camera* pCamera);

	~Skybox();
    
    bool init(const std::string& Directory,
              const std::string& PosXFilename,
              const std::string& NegXFilename,
              const std::string& PosYFilename,
              const std::string& NegYFilename,
              const std::string& PosZFilename,
              const std::string& NegZFilename);
    
    void render();

private:
	const Camera* m_pCamera;
    glimac::CubemapTexture* m_pCubemapTex;
};

#endif