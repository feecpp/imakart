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
  virtual const bool isSelected() const = 0;
};

#endif // INTERFACEELEMENT_HPP

