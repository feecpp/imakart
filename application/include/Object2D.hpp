#ifndef OBJECT2D_HPP
#define OBJECT2D_HPP

class InterfaceElement;

/**
 * @brief Classe abstraite représentant un objet 2D capable de se dessiner.
 */
class Object2D
{
public:
  virtual void draw() = 0;

  void setModelToRepresent(const InterfaceElement& myModel)
    {model = &myModel;}

  const InterfaceElement* getModel()
	{return model;}
	
protected:
  const InterfaceElement* model;

};

#endif // OBJECT3D_HPP

