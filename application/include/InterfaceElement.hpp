#ifndef INTERFACEELEMENT_HPP
#define INTERFACEELEMENT_HPP

#include <glm/glm.hpp>
#include <string>

/**
 * @brief The Positionable interface
 * Fait le lien entre le moteur 3D et le moteur de jeu
 */
class InterfaceElement
{
public:
  virtual ~InterfaceElement() {}
  virtual const bool isSelected() const = 0;

  const std::string& getName() const
	{return name;}

  virtual float getTime() const
    {return 0;}

  virtual const glm::vec3 getPosition() const
  	{return glm::vec3(0);}

protected:
  std::string name;
};

#endif // INTERFACEELEMENT_HPP

