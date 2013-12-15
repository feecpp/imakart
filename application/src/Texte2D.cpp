#include "Texte2D.hpp"
#include <iostream>

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
}

Texte2D::~Texte2D(){

}
