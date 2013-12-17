#include "Skybox.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Skybox::Skybox(const Camera* pCamera)
	: m_pCamera(pCamera), m_pCubemapTex(nullptr)
	{
    //BACK
    vertices[0] = glimac::Vertex3DSimple(glm::vec3(-0.5f, 0.9f, -0.5f));
    vertices[1] = glimac::Vertex3DSimple(glm::vec3(0.5f, 0.9f, -0.5f));
    vertices[2] = glimac::Vertex3DSimple(glm::vec3(0.5f, -0.1f, -0.5f));
    vertices[3] = glimac::Vertex3DSimple(glm::vec3(-0.5f, -0.1f, -0.5f));

    //TOP
    vertices[4] = glimac::Vertex3DSimple(glm::vec3(-0.5f, 0.9f, -0.5f));
    vertices[5] = glimac::Vertex3DSimple(glm::vec3(0.5f, 0.9f, -0.5f));
    vertices[6] = glimac::Vertex3DSimple(glm::vec3(0.5f, 0.9f, 0.5f));
    vertices[7] = glimac::Vertex3DSimple(glm::vec3(-0.5f, 0.9f, 0.5f));

    //RIGHT
    vertices[8] = glimac::Vertex3DSimple(glm::vec3(0.5f, 0.9f, -0.5f));
    vertices[9] = glimac::Vertex3DSimple(glm::vec3(0.5f, -0.1f, -0.5f));
    vertices[10] = glimac::Vertex3DSimple(glm::vec3(0.5f, -0.1f, 0.5f));
    vertices[11] = glimac::Vertex3DSimple(glm::vec3(0.5f, 0.9f, 0.5f));

    //BOTTOM
    vertices[12] = glimac::Vertex3DSimple(glm::vec3(0.5f, -0.1f, -0.5f));
    vertices[13] = glimac::Vertex3DSimple(glm::vec3(0.5f, -0.1f, 0.5f));
    vertices[14] = glimac::Vertex3DSimple(glm::vec3(-0.5f, -0.1f, 0.5f));
    vertices[15] = glimac::Vertex3DSimple(glm::vec3(-0.5f, -0.1f, -0.5f));

    //LEFT
    vertices[16] = glimac::Vertex3DSimple(glm::vec3(-0.5f, 0.9f, -0.5f));
    vertices[17] = glimac::Vertex3DSimple(glm::vec3(-0.5f, -0.1f, -0.5f));
    vertices[18] = glimac::Vertex3DSimple(glm::vec3(-0.5f, -0.1f, 0.5f));
    vertices[19] = glimac::Vertex3DSimple(glm::vec3(-0.5f, 0.9f, 0.5f));

    //FRONT
    vertices[20] = glimac::Vertex3DSimple(glm::vec3(0.5f, 0.9f, 0.5f));
    vertices[21] = glimac::Vertex3DSimple(glm::vec3(0.5f, -0.1f, 0.5f));
    vertices[22] = glimac::Vertex3DSimple(glm::vec3(-0.5f, -0.1f, 0.5f));
    vertices[23] = glimac::Vertex3DSimple(glm::vec3(-0.5f, 0.9f, 0.5f));
  }  


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

    setVBO();
    setVAO();
    return true;
}

void Skybox::setVBO(){
  vbo.setBufferData((const GLvoid* ) vertices, sizeof(vertices), GL_STATIC_DRAW);
}

void Skybox::setVAO(){
  vao.enableVertexAttribArray(0);
  vao.vertexAttribPointer(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3DSimple), (const GLvoid* ) offsetof(glimac::Vertex3DSimple, position));
}

void Skybox::render(const glimac::ShaderProgram& shaderProgram) const
{   

    glDepthMask (GL_FALSE);

    glm::mat4 modelMatrix = glm::mat4(glm::vec4(40,0,0,0),glm::vec4(0,40,0,0),glm::vec4(0,0,40,0), glm::vec4(0,0,0,1));
    GLint modelIndex = shaderProgram.getUniformIndex("model");
    GLint diffuseIndex = shaderProgram.getUniformIndex("material.diffuse");
    GLint textureIndex = shaderProgram.getUniformIndex("cube_texture");

    shaderProgram.setUniform(modelIndex, modelMatrix);
    m_pCubemapTex->Bind(GL_TEXTURE0);
    shaderProgram.setUniform(textureIndex, 0);
    
    vao.bind();
    for(unsigned int i = 0; i < 24; i = i+4){
      if(i == 12){
        shaderProgram.setUniform(diffuseIndex, glm::vec4(0.6,0.6,0.6,1));
      }else{
        shaderProgram.setUniform(diffuseIndex, glm::vec4(0,0,1,1));
      }
      glDrawArrays(GL_TRIANGLE_FAN, i, 4);
    }
    vao.unbind();

    glDepthMask (GL_TRUE);
}