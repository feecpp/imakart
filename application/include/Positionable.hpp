#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

/**
 * @brief The Positionable interface
 * Fait le lien entre le moteur 3D et le moteur de jeu
 */
class Positionable
{
public:
  virtual ~Positionable() {}

  virtual const glm::vec3& getPosition() const = 0;
  virtual const glm::quat& getOrientation() const = 0;
};

#endif // POSITIONABLE_HPP
