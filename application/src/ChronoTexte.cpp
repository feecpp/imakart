#include "ChronoTexte.hpp"
#include <iostream>
#include <sstream>

ChronoTexte::ChronoTexte(){
  texture = new glimac::Texture(GL_TEXTURE_2D);
  texture->loadTexture2D("textures/fontInversed.png");
  timer = 0.f;
  model = nullptr;
}

void ChronoTexte::printChronoTexte(int x, int y, int size, const glimac::ShaderProgram& shaderProgram)
{
  std::ostringstream os;
  os << timer;
  std::string time = os.str();
  std::string text = "time: "+time;
  //std::cout << "text :" << text << std::endl;
  unsigned int length = text.size();

  vertices.clear();
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


  setVBO();
  setVAO();

  //Dessin du texte
  vao.bind();
  GLint Text2DUniform = shaderProgram.getUniformIndex("myTextureSampler");
  shaderProgram.setUniform(Text2DUniform, 0);
  texture->bind();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  glDisable(GL_BLEND);
  texture->unbind();
  vao.unbind();
}

void ChronoTexte::draw(const glimac::ShaderProgram& shaderProgram){
  printChronoTexte(10, 570, 20, shaderProgram);
}

void ChronoTexte::setVBO(){

  glimac::Vertex2DUV verticesForVBO[vertices.size()];
  for(unsigned int i=0; i< vertices.size(); ++i){
    verticesForVBO[i] = vertices[i];
  }
  vbo.setBufferData(verticesForVBO, sizeof(verticesForVBO), GL_STATIC_DRAW);
}

void ChronoTexte::setVAO(){
  vao.enableVertexAttribArray(0);
  vao.enableVertexAttribArray(1);
  vao.vertexAttribPointer(vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (0 * sizeof(GLfloat)) );
  vao.vertexAttribPointer(vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (2 * sizeof(GLfloat)) );
}

void ChronoTexte::update(){
  if(model != nullptr)
    timer = model->getTime();
}

ChronoTexte::~ChronoTexte(){

}
