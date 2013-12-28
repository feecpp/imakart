#ifndef OBJECTTEXTE_HPP
#define OBJECTTEXTE_HPP

#include <GL/glew.h>
#include <ShaderProgram.hpp>
#include "Texture.hpp"

#include <vector>

class InterfaceElement;

/**
 * @brief Classe abstraite représentant un objet de texte capable de se dessiner.
 */
class ObjectTexte
{
public:
  virtual ~ObjectTexte() {
    texture = NULL;
  }

  virtual void draw(const glimac::ShaderProgram& shaderProgram) const = 0;
  virtual void update() = 0;
  virtual void setPosition(int x, int y, int size) = 0;

  void setModelToRepresent(const InterfaceElement& myModel)
    {model = &myModel;}

  const InterfaceElement* getModel() const
  {return model;}

  glimac::Texture* getTexture() const
  { return texture;}

protected:
  const InterfaceElement* model;
  glimac::Texture* texture; //Pointeur sur la texture active

};

#endif // OBJECTTEXTE_HPP

