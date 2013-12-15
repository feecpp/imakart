#include "CubeMapTexture.hpp"

using namespace glimac;


static const GLenum types[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                                  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                                  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };


CubemapTexture::CubemapTexture(const std::string& Directory,
                               const std::string& PosXFilename,
                               const std::string& NegXFilename,
                               const std::string& PosYFilename,
                               const std::string& NegYFilename,
                               const std::string& PosZFilename,
                               const std::string& NegZFilename)
{
    std::string::const_iterator it = Directory.end();
    it--;
    std::string BaseDir = (*it == '/') ? Directory : Directory + "/";
    
    m_fileNames[0] = BaseDir + PosXFilename;
    m_fileNames[1] = BaseDir + NegXFilename;
    m_fileNames[2] = BaseDir + PosYFilename;
    m_fileNames[3] = BaseDir + NegYFilename;
    m_fileNames[4] = BaseDir + PosZFilename;
    m_fileNames[5] = BaseDir + NegZFilename;
    
    m_textureObj = 0;
}

CubemapTexture::~CubemapTexture()
{
    if (m_textureObj != 0) {
        glDeleteTextures(1, &m_textureObj);
    }
}
    
bool CubemapTexture::Load()
{
    glGenTextures(1, &m_textureObj);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);

    for (unsigned int i = 0 ; i < (sizeof(types)/sizeof(types[0])) ; i++) {
        sf::Image image;
        if(image.loadFromFile(m_fileNames[i]))
        {
            glTexImage2D(types[i], 0, GL_RGB, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        }else{
            return false;
        }
    }    
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);           
    
    return true;
}

    
void CubemapTexture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
}
