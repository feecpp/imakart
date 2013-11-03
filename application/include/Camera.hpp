#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Positionable;

class Camera
{
public:
  Camera(size_t windowWidth, size_t windowHeight);

  const glm::vec3 getPosition() const;
  const glm::vec3 getWhereILook() const;
  const glm::mat4& getViewProjectionMatrix() const;
  void updateViewProjectionMatrix();

  void linkToPositionable(const Positionable& objectToFollow)
    {this->objectToFollow = &objectToFollow;}

private:
  const Positionable* objectToFollow;
  glm::mat4 viewProjection;

  size_t windowWidth;
  size_t windowHeight;
};

#endif // CAMERA_HPP
