#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Positionable;

class Camera
{
public:
  const glm::vec3 getPosition() const;
  const glm::vec3 getWhereILook() const;

  void linkToPositionable(const Positionable& objectToFollow)
    {this->objectToFollow = &objectToFollow;}

private:
  const Positionable* objectToFollow;
};

#endif // CAMERA_HPP
