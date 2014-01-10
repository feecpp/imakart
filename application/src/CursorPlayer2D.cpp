#include "CursorPlayer2D.hpp"
#include <iostream>

CursorPlayer2D::CursorPlayer2D()
{
  vertices[0] = glimac::Vertex2DUV(glm::vec2(-0.5f, -0.5f), glm::vec2(0,1));
  vertices[1] = glimac::Vertex2DUV(glm::vec2(0.5f, -0.5f), glm::vec2(1,1));
  vertices[2] = glimac::Vertex2DUV(glm::vec2(0.5f, 0.5f), glm::vec2(1,0));
  vertices[3] = glimac::Vertex2DUV(glm::vec2(-0.5f, 0.5f), glm::vec2(0,0));

  setVBO();
  setVAO();
}

CursorPlayer2D::CursorPlayer2D(const float x_bottom, const float y_left, const float width, const float height, const std::string pathTexture)
{
  vertices[0] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left), glm::vec2(0,1));
  vertices[1] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left), glm::vec2(1,1));
  vertices[2] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left + height), glm::vec2(1,0));
  vertices[3] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left + height), glm::vec2(0,0));

  glimac::Texture* texture = new glimac::Texture(GL_TEXTURE_2D);
  texture->loadTexture2D(pathTexture);
  tabTexture.push_back(texture);

  activTexture = tabTexture[0];

  setVBO();
  setVAO();
}

CursorPlayer2D::~CursorPlayer2D()
{
}

const glimac::Vertex2DUV* CursorPlayer2D::getVertices() const{
  return vertices;
}

void CursorPlayer2D::setVBO(){
  vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
}

void CursorPlayer2D::setVAO(){
  vao.enableVertexAttribArray(0);
  vao.enableVertexAttribArray(1);
  vao.vertexAttribPointer(vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (0 * sizeof(GLfloat)) );
  vao.vertexAttribPointer(vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (2 * sizeof(GLfloat)) );
}

void CursorPlayer2D::draw(const glimac::ShaderProgram& shaderProgram) const{
  vao.bind();
  GLint locationUTexture = shaderProgram.getUniformIndex("uTexture");
  GLint locationUMat = shaderProgram.getUniformIndex("uModelMatrix");
    shaderProgram.setUniform(locationUTexture, 0);
    shaderProgram.setUniform(locationUMat, glm::mat3(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,1)));
  activTexture->bind();
  glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisable(GL_BLEND);
  activTexture->unbind();
  vao.unbind();
}

void CursorPlayer2D::updateVertices(const float x_bottom, const float y_left, const float width, const float height){
  vertices[0] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left), glm::vec2(0,1));
  vertices[1] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left), glm::vec2(1,1));
  vertices[2] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left + height), glm::vec2(1,0));
  vertices[3] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left + height), glm::vec2(0,0));
  setVBO();
  setVAO();
}

void CursorPlayer2D::update(){
  const glm::vec3 position = model->getPosition();
  float x = 0.85 + ((position[0]-340) * 0.5 / 510)/1.3;
  float y = -0.7 - ((position[2]-150) * 0.5 / 510)/1.5;
  std::cout << "position : " << position[0] << ", "<< position[2] << std::endl;
  std::cout << "position : " << x << ", "<< y << std::endl;
  updateVertices(x, y, 0.02, 0.02);
}
