#ifndef INTERFACEELEMENT_HPP
#define INTERFACEELEMENT_HPP

#include <glm/glm.hpp>

/**
 * @brief The Positionable interface
 * Fait le lien entre le moteur 3D et le moteur de jeu
 */
class InterfaceElement
{
public:
  virtual ~InterfaceElement() {}
  virtual const bool isSelected() const = 0;

  const char* getName() const
	{return name;}

  virtual float getTime() const
    {return 0;}

protected:
  const char* name;
};

#endif // INTERFACEELEMENT_HPP

