#include "ItemGraphic2D.hpp"
#include <iostream>

ItemGraphic2D::ItemGraphic2D()
  :oldItem(false)
{
  vertices[0] = glimac::Vertex2DUV(glm::vec2(-0.5f, -0.5f), glm::vec2(0,1));
  vertices[1] = glimac::Vertex2DUV(glm::vec2(0.5f, -0.5f), glm::vec2(1,1));
  vertices[2] = glimac::Vertex2DUV(glm::vec2(0.5f, 0.5f), glm::vec2(1,0));
  vertices[3] = glimac::Vertex2DUV(glm::vec2(-0.5f, 0.5f), glm::vec2(0,0));

  setVBO();
  setVAO();
}

ItemGraphic2D::ItemGraphic2D(const float x_bottom, const float y_left, const float width, const float height, const std::string pathTexture)
  :oldItem(false)
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

ItemGraphic2D::~ItemGraphic2D()
{
}

const glimac::Vertex2DUV* ItemGraphic2D::getVertices() const{
  return vertices;
}

void ItemGraphic2D::setVBO(){
  vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
}

void ItemGraphic2D::setVAO(){
  vao.enableVertexAttribArray(0);
  vao.enableVertexAttribArray(1);
  vao.vertexAttribPointer(vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (0 * sizeof(GLfloat)) );
  vao.vertexAttribPointer(vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (2 * sizeof(GLfloat)) );
}

void ItemGraphic2D::draw(const glimac::ShaderProgram& shaderProgram) const{
  vao.bind();
  GLint locationUTexture = shaderProgram.getUniformIndex("uTexture");
  GLint locationUMat = shaderProgram.getUniformIndex("uModelMatrix");
    shaderProgram.setUniform(locationUTexture, 0);
    shaderProgram.setUniform(locationUMat, glm::mat3(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,1)));
  activTexture->bind();
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  activTexture->unbind();
  vao.unbind();
}

void ItemGraphic2D::setNewTexture(const std::string pathTexture){
  for (size_t i = 0; i < tabTexture.size(); ++i)
  {
    delete tabTexture[i];
  }

  tabTexture.erase(tabTexture.begin(), tabTexture.end());

  glimac::Texture* texture = new glimac::Texture(GL_TEXTURE_2D);
  texture->loadTexture2D(pathTexture);
  tabTexture.push_back(texture);  

  activTexture = tabTexture[0];
}

void ItemGraphic2D::update(){
  //Si l'item a été utilisé
  if(model->isSelected() && oldItem == false){
    setNewTexture("textures/items/noItem.png");
    oldItem = true;
  }else if(!model->isSelected() && oldItem == true){
    std::string path = "textures/items/";
    path = path + model->getName();
    path = path + ".png";
    setNewTexture(path);
    oldItem = false;
  }
}
