#include "Texte2D.hpp"
#include <iostream>

Texte2D::Texte2D(){
  //Inutile, juste pr redéfinir les méthodes virtuelles de object2D
}

Texte2D::Texte2D(std::string text, int x, int y, int size)
{
  unsigned int length = text.size();

  for ( unsigned int i=0 ; i<length ; ++i ){

    char character = text[i];
    float uv_x = (character%16)/16.0f;
    float uv_y = (character/16)/16.0f;

    glimac::Vertex2DUV up_left = glimac::Vertex2DUV(glm::vec2(x+i*size, y+size), glm::vec2(uv_x, 1.0f - uv_y));
    glimac::Vertex2DUV up_right = glimac::Vertex2DUV(glm::vec2(x+i*size+size, y+size), glm::vec2( uv_x+1.0f/16.0f, 1.0f - uv_y ));
    glimac::Vertex2DUV down_right = glimac::Vertex2DUV(glm::vec2(x+i*size+size, y), glm::vec2( uv_x+1.0f/16.0f, 1.0f - (uv_y + 1.0f/16.0f) ));
    glimac::Vertex2DUV down_left = glimac::Vertex2DUV(glm::vec2(x+i*size, y), glm::vec2( uv_x, 1.0f - (uv_y + 1.0f/16.0f)));

    //Triangles
    vertices.push_back(up_left);
    vertices.push_back(down_left);
    vertices.push_back(up_right);

    vertices.push_back(down_right);
    vertices.push_back(up_right);
    vertices.push_back(down_left);
  }

  glimac::Vertex2DUV verticesForVBO[vertices.size()];
  for(unsigned int i=0; i< vertices.size(); ++i){
    verticesForVBO[i] = vertices[i];
  }

  texture = new glimac::Texture(GL_TEXTURE_2D);
  texture->loadTexture2D("textures/font.png");

  setVBO(verticesForVBO);
  setVAO();
}

void Texte2D::draw(const glimac::ShaderProgram& shaderProgram) const{
  vao.bind();
  GLint Text2DUniform = shaderProgram.getUniformIndex("myTextureSampler");
  //GLint locationUMat = shaderProgram.getUniformIndex("uModelMatrix");
    shaderProgram.setUniform(Text2DUniform, 0);
    //shaderProgram.setUniform(locationUMat, glm::mat3(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,1)));
  texture->bind();
  glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
  texture->unbind();
  vao.unbind();
}

void Texte2D::setVBO(glimac::Vertex2DUV vertices[]){
  vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
}

void Texte2D::setVAO(){
  vao.enableVertexAttribArray(0);
  vao.enableVertexAttribArray(1);
  vao.vertexAttribPointer(vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (0 * sizeof(GLfloat)) );
  vao.vertexAttribPointer(vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (2 * sizeof(GLfloat)) );
}

void Texte2D::update(){
  //Inutile, juste pr redéfinir les méthodes virtuelles de object2D
}


Texte2D::~Texte2D(){

}
