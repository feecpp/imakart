#ifndef OBJECT2D_HPP
#define OBJECT2D_HPP

#include <GL/glew.h>
#include <ShaderProgram.hpp>
#include "Texture.hpp"

#include <vector>

class InterfaceElement;

/**
 * @brief Classe abstraite représentant un objet 2D capable de se dessiner.
 */
class Object2D
{
public:
  virtual ~Object2D() {
    activTexture = NULL;
    for(unsigned int i = 0; i < tabTexture.size(); ++i){
      delete tabTexture[i];
    }
    tabTexture.erase(tabTexture.begin(), tabTexture.end());
  }
  
  virtual void draw(const glimac::ShaderProgram& shaderProgram) const = 0;
  virtual void update() = 0;

  void setModelToRepresent(const InterfaceElement& myModel)
    {model = &myModel;}

//  void setTexture(const GLuint& myIdTexture, const GLuint& myIdTextureSelect)
  /*	{idTexture[1] = myIdTexture; idTexture[0] = myIdTextureSelect; activTexture = myIdTexture;}*/

  const InterfaceElement* getModel() const
	{return model;}

  glimac::Texture* getActivTexture() const
  { return activTexture;}
	
protected:
  const InterfaceElement* model;
  std::vector <glimac::Texture* > tabTexture; //Tableau contenant les deux textures de l'objet (select, non select)
  glimac::Texture* activTexture; //Pointeur sur la texture active

};

#endif // OBJECT3D_HPP

