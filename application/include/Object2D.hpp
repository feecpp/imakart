#ifndef OBJECT2D_HPP
#define OBJECT2D_HPP

#include <GL/glew.h>
#include <ShaderProgram.hpp>

class InterfaceElement;

/**
 * @brief Classe abstraite représentant un objet 2D capable de se dessiner.
 */
class Object2D
{
public:
  virtual ~Object2D() {}
  
  virtual void draw(const glimac::ShaderProgram& shaderProgram) const = 0;
  virtual void update() = 0;

  void setModelToRepresent(const InterfaceElement& myModel)
    {model = &myModel;}

  void setTexture(const GLuint& myIdTexture, const GLuint& myIdTextureSelect)
  	{idTexture[1] = myIdTexture; idTexture[0] = myIdTextureSelect; activTexture = myIdTexture;}

  const InterfaceElement* getModel() const
	{return model;}

  GLuint getActivTexture() const
  { return activTexture;}
	
protected:
  const InterfaceElement* model;
  GLuint idTexture[2];
  GLuint activTexture;

};

#endif // OBJECT3D_HPP

