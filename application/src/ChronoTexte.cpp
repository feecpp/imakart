#include "ChronoTexte.hpp"
#include <iostream>
#include <sstream>
#include <string>

ChronoTexte::ChronoTexte(){
  texture = new glimac::Texture(GL_TEXTURE_2D);
  texture->loadTexture2D("textures/fontInversed2.png");
  timer = 0.f;
  model = nullptr;
}


std::string ChronoTexte::prepareText() const
{
  int minutes, seconds;
  float centisecs;

  //Calcul du format minutes/secondes/centièmes
  minutes = timer /60;
  seconds = (int)(timer)%60;
  centisecs = timer - (int)(timer);

  std::string time;
  centisecs = (int)(centisecs*100);

  //Passage en string pour des minutes
  std::ostringstream conversionMin;
  conversionMin << minutes;
  std::string s_minutes = "";
  if(minutes < 10){
    s_minutes = "0";
    s_minutes += conversionMin.str();
  }else if(minutes == 0){
    s_minutes = "00";
  }else{
    s_minutes = conversionMin.str();
  }
  time = s_minutes + std::string(":");

  //Passage en string pour des secondes
  std::ostringstream conversionSec;
  conversionSec << seconds;
  std::string s_seconds = "";
  if(seconds < 10){
    s_seconds = "0";
    s_seconds += conversionSec.str();
  }else if(seconds == 0){
    s_seconds = "00";
  }else{
    s_seconds = conversionSec.str();
  }
  time = time + s_seconds + std::string(":");

  //Passage en string pour des centièmes
  std::ostringstream conversionCent;
  conversionCent << (int)(centisecs);
  std::string s_centisecs = "";
  if((int)(centisecs) < 10){
    s_centisecs = "0";
    s_centisecs += conversionCent.str();
  }else if((int)(centisecs) == 0){
    s_centisecs = "00";
  }else{
    s_centisecs = conversionCent.str();
  }
  time = time + s_centisecs;

  return time;
}

void ChronoTexte::draw(const glimac::ShaderProgram& shaderProgram) const
{
  //Dessin du texte
  vao.bind();
  GLint Text2DUniform = shaderProgram.getUniformIndex("myTextureSampler");
  shaderProgram.setUniform(Text2DUniform, 0);
  texture->bind();

  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.8);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  glDisable(GL_BLEND);

  glDisable(GL_ALPHA_TEST);

  texture->unbind();
  vao.unbind();
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

  setPosition(position.x, position.y, size);
}

void ChronoTexte::setPosition(int x, int y, int size)
{
  position.x = x; position.y = y; this->size = size;//Pour garder en mémoire et utilsier dans update

  //Je suppose que ces variables devraient pouvoir etre definies
  std::string time = prepareText();
  std::string text = "Chrono : "+time;
  unsigned int length = text.size();

  vertices.clear();
  for (unsigned int i=0 ; i < length ; ++i )
  {
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
}

ChronoTexte::~ChronoTexte(){
}
