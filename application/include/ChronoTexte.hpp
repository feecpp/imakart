#ifndef CHRONOTEXTE_HPP
#define CHRONOTEXTE_HPP

#include <vector>
#include <string>
#include <ShaderProgram.hpp>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Texture.hpp"
#include "Vertex2DRGB.hpp"
#include "ObjectTexte.hpp"
#include "InterfaceElement.hpp"

class ChronoTexte : public ObjectTexte
{
public:
  ChronoTexte();
  void printChronoTexte(int x, int y, int size, const glimac::ShaderProgram& shaderProgram);
  ~ChronoTexte();

  void draw(const glimac::ShaderProgram& shaderProgram);
  void update();

private:
  std::vector<glimac::Vertex2DUV> vertices;
  glimac::LowLevelVBO vbo;
  glimac::VAO vao;
  float timer;
  void setVBO(); //called in the constructor
  void setVAO(); //called in the constructor
  std::string prepareText();
};

#endif // CHRONOTEXTE_HPP
