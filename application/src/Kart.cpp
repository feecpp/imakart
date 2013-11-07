#include "Kart.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Kart::Kart()
  : position(0.f, 0.f, 0.f), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))), directionAngle(0.f), speed(0.f)
{
}

Kart::Kart(glm::vec3 position, glm::quat orientation, float speed)
  : position(position), orientation(orientation), speed(speed)
{
}

// The Kart goes forward : its position changes
void Kart::moveForward(){
  const glm::vec3 initialDirection = glm::vec3(0.f, 0.f, -1.f);
  glm::vec3 direction = glm::toMat3(orientation) * initialDirection;
  position += direction;
}

//The Kart goes back : its position changes
void Kart::moveBackward(){
  const glm::vec3 initialDirection = glm::vec3(0.f, 0.f, -1.f);
  glm::vec3 direction = glm::toMat3(orientation) * initialDirection;
  position -= direction;
}

// The Kart goes left : its orientation changes
void Kart::turnLeft(){
  directionAngle += 10.f;
  orientation = glm::angleAxis(directionAngle, glm::vec3(0.f, 1.f, 0.f));
}

// The Kart goes right : its orientation changes
void Kart::turnRight(){
  directionAngle -= 10.f;
  orientation= glm::angleAxis(directionAngle, glm::vec3(0.f, 1.f, 0.f));
}

const glm::vec3& Kart::getPosition() const
  {return position;}

const glm::quat& Kart::getOrientation() const
  {return orientation;}
