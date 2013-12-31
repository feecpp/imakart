#ifndef ITEMGRAPHIC2D_HPP
#define ITEMGRAPHIC2D_HPP

#include "Object2D.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Texture.hpp"
#include "Vertex2DRGB.hpp"
#include "InterfaceElement.hpp"

class ItemGraphic2D : public Object2D
{
public:
  ItemGraphic2D(); // Default
  ItemGraphic2D(const float x_bottom, const float y_left, const float width, const float height, const std::string pathTexture); 
  ~ItemGraphic2D();

  const glimac::Vertex2DUV* getVertices() const;

  void updateVertices(const float x_bottom, const float y_left, const float width, const float height);

  void draw(const glimac::ShaderProgram& shaderProgram) const;

  void setNewTexture(const std::string pathTexture);

  void update();

protected:
  glimac::Vertex2DUV vertices[4];
  glimac::LowLevelVBO vbo;
  glimac::VAO vao;

  void setVBO(); //call in the constructor
  void setVAO(); //call in the constructor

  bool oldItem;
};

#endif