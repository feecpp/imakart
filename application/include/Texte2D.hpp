#ifndef Texte2D_HPP
#define Texte2D_HPP

#include <vector>
#include <string>
#include <ShaderProgram.hpp>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Texture.hpp"
#include "Vertex2DRGB.hpp"
#include "Chrono.hpp"
class Texte2D
{
public:
  Texte2D();
  void printTexte2D(int x, int y, int size, const glimac::ShaderProgram& shaderProgram);
  ~Texte2D();

  void draw(const glimac::ShaderProgram& shaderProgram) const;
  void update();
  void setModelToRepresent(Chrono& chrono);
  Chrono* getModel();

private:
  std::vector<glimac::Vertex2DUV> vertices;
  glimac::LowLevelVBO vbo;
  glimac::VAO vao;
  glimac::Texture* texture;
  float timer;
  void setVBO(); //called in the constructor
  void setVAO(); //called in the constructor
  Chrono* model;
};

#endif // Texte2D_HPP
