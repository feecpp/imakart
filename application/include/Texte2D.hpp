#ifndef Texte2D_HPP
#define Texte2D_HPP

#include <vector>
#include <string>
#include <ShaderProgram.hpp>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Texture.hpp"
#include "Vertex2DRGB.hpp"

class Texte2D
{
public:
  Texte2D();
  void printTexte2D(std::string text, int x, int y, int size, const glimac::ShaderProgram& shaderProgram);
  ~Texte2D();

  void draw(const glimac::ShaderProgram& shaderProgram) const;
  void update(float time);

private:
  std::vector<glimac::Vertex2DUV> vertices;
  glimac::LowLevelVBO vbo;
  glimac::VAO vao;
  glimac::Texture* texture;
  float timer;
  void setVBO(); //called in the constructor
  void setVAO(); //called in the constructor
};

#endif // Texte2D_HPP
