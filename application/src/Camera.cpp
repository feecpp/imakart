#include "Camera.hpp"
#include "Positionable.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(size_t windowWidth, size_t windowHeight)
  : objectToFollow(nullptr), windowWidth(windowWidth), windowHeight(windowHeight)
{
}

const glm::vec3 Camera::getPosition() const
{
  if (objectToFollow != nullptr)
    return  (objectToFollow->getPosition() - objectToFollow->getOrientation()) + glm::vec3(0.f, 2.f, 0.f);
  else
    return glm::vec3(0.f, 0.f, 0.f);
}

const glm::vec3 Camera::getWhereILook() const
{
  //TODO : faire regarder la caméra le nez un peu relevé par rapport à l'objet
  //qu'elle suit
  if (objectToFollow != nullptr)
    return objectToFollow->getPosition();
  else
    return glm::vec3(0.f, 0.f, -100.f);
}

const glm::mat4&Camera::getViewProjectionMatrix() const
{
  return viewProjection;
}

void Camera::updateViewProjectionMatrix()
{
  viewProjection = glm::lookAt(getPosition(), getWhereILook(), glm::vec3(0.f, 1.f, 0.f));
  viewProjection =  glm::perspective(90.f, windowWidth / (float) windowHeight, 0.1f, 1000.f) * viewProjection;
}

