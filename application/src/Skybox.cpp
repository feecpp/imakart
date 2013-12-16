#include "Skybox.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Skybox::Skybox(const Camera* pCamera)
	: m_pCamera(pCamera), m_pCubemapTex(nullptr)
	{
    //BACK
    vertices[0] = glimac::Vertex3D(glm::vec3(-0.5f, 1.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[1] = glimac::Vertex3D(glm::vec3(0.5f, 1.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[2] = glimac::Vertex3D(glm::vec3(0.5f, 0.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[3] = glimac::Vertex3D(glm::vec3(-0.5f, 0.f, -0.5f), glm::vec2(1,0), glm::vec3(1));

    //TOP
    vertices[4] = glimac::Vertex3D(glm::vec3(-0.5f, 1.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[5] = glimac::Vertex3D(glm::vec3(0.5f, 1.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[6] = glimac::Vertex3D(glm::vec3(0.5f, 1.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[7] = glimac::Vertex3D(glm::vec3(-0.5f, 1.f, 0.5f), glm::vec2(1,0), glm::vec3(1));

    //RIGHT
    vertices[8] = glimac::Vertex3D(glm::vec3(0.5f, 1.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[9] = glimac::Vertex3D(glm::vec3(0.5f, 0.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[10] = glimac::Vertex3D(glm::vec3(0.5f, 0.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[11] = glimac::Vertex3D(glm::vec3(0.5f, 1.f, 0.5f), glm::vec2(1,0), glm::vec3(1));

    //BOTTOM
    vertices[12] = glimac::Vertex3D(glm::vec3(0.5f, 0.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[13] = glimac::Vertex3D(glm::vec3(0.5f, 0.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[14] = glimac::Vertex3D(glm::vec3(-0.5f, 0.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[15] = glimac::Vertex3D(glm::vec3(-0.5f, 0.f, -0.5f), glm::vec2(1,0), glm::vec3(1));

    //LEFT
    vertices[16] = glimac::Vertex3D(glm::vec3(-0.5f, 1.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[17] = glimac::Vertex3D(glm::vec3(-0.5f, 0.f, -0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[18] = glimac::Vertex3D(glm::vec3(-0.5f, 0.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[19] = glimac::Vertex3D(glm::vec3(-0.5f, 1.f, 0.5f), glm::vec2(1,0), glm::vec3(1));

    //FRONT
    vertices[20] = glimac::Vertex3D(glm::vec3(0.5f, 1.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[21] = glimac::Vertex3D(glm::vec3(0.5f, 0.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[22] = glimac::Vertex3D(glm::vec3(-0.5f, 0.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
    vertices[23] = glimac::Vertex3D(glm::vec3(-0.5f, 1.f, 0.5f), glm::vec2(1,0), glm::vec3(1));
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
  vao.enableVertexAttribArray(1);
  vao.enableVertexAttribArray(2);
  vao.vertexAttribPointer(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid* ) offsetof(glimac::Vertex3D, position));
  vao.vertexAttribPointer(vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid* ) offsetof(glimac::Vertex3D, textureCoordinates));
  vao.vertexAttribPointer(vbo, 2, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex3D), (const GLvoid* ) offsetof(glimac::Vertex3D, normal));
}

void Skybox::render(const glimac::ShaderProgram& shaderProgram) const
{   
    GLint OldCullFaceMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
    GLint OldDepthFuncMode;
    glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
    
    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);
    
    //Ajouter code de dessin ici 
    glm::mat4 modelMatrix = glm::mat4(glm::vec4(20,0,0,0),glm::vec4(0,20,0,0),glm::vec4(0,0,20,0), glm::vec4(0,0,0,1));
    GLint modelIndex = shaderProgram.getUniformIndex("model");
    GLint diffuseIndex = shaderProgram.getUniformIndex("material.diffuse");

    shaderProgram.setUniform(modelIndex, modelMatrix);
    m_pCubemapTex->Bind(GL_TEXTURE0);
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

    glCullFace(OldCullFaceMode);        
    glDepthFunc(OldDepthFuncMode);
}