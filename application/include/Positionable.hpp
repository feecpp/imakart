#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include <glm/glm.hpp>

/**
 * @brief The Positionable interface
 * Fait le lien entre le moteur 3D et le moteur de jeu
 */
class Positionable
{
public:
  virtual const glm::vec3& getPosition() const = 0;
  virtual const glm::vec3& getOrientation() const = 0;
};

#endif // POSITIONABLE_HPP
