#include "Skybox.hpp"

Skybox::Skybox(const Camera* pCamera)
	: m_pCamera(pCamera), m_pCubemapTex(nullptr)
	{}


Skybox::~Skybox()
{}


bool Skybox::init(const std::string& Directory,
                  const std::string& PosXFilename,
                  const std::string& NegXFilename,
                  const std::string& PosYFilename,
                  const std::string& NegYFilename,
                  const std::string& PosZFilename,
                  const std::string& NegZFilename)
{
    m_pCubemapTex = new glimac::CubemapTexture(Directory,
                                       PosXFilename,
                                       NegXFilename,
                                       PosYFilename,
                                       NegYFilename,
                                       PosZFilename,
                                       NegZFilename);

    if (!m_pCubemapTex->Load()) {
        return false;
    }

    return true;
}


void Skybox::render()
{   
    GLint OldCullFaceMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
    GLint OldDepthFuncMode;
    glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
    
    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);
    
    //Ajouter code de dessin ici 
    m_pCubemapTex->Bind(GL_TEXTURE0);

    glCullFace(OldCullFaceMode);        
    glDepthFunc(OldDepthFuncMode);
}