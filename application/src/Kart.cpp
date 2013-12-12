#include "Kart.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <SFML/System.hpp>
#include <iostream>

Kart::Kart()
    : position(0.f, 0.f, 0.f), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))),
      directionAngle(0.f), speed(0.f), currentAngularSpeed(0.f), currentAcceleration(0.f)
{
}

Kart::Kart(glm::vec3 position, glm::quat orientation, float speed)
  : position(position), orientation(orientation), speed(speed)
{
}

Kart::~Kart()
{
}

void Kart::update(float elapsedTimeInSecond)
{
  //Calcul de la nouvelle direction en fonction de l'angularSpeed
  if (speed != 0.f)
  {
    directionAngle += currentAngularSpeed * (elapsedTimeInSecond); //en degres/secondes
  }
  orientation = glm::angleAxis(directionAngle, glm::vec3(0.f, 1.f, 0.f));

  const glm::vec3 initialDirection = glm::vec3(0.f, 0.f, -1.f);
  glm::vec3 direction = glm::normalize(glm::toMat3(orientation) * initialDirection);

  //Tentative d'implémentation d'une base de physique : http://www.onversity.net/cgi-bin/progactu/actu_aff.cgi?Eudo=bgteob&P=00000551
  float travelledDistance = speed * elapsedTimeInSecond + currentAcceleration * (elapsedTimeInSecond * elapsedTimeInSecond) / 2.f;
  position += direction * travelledDistance;//en uniteOGL/seconde

  //Update speed for next calculation ! (speed = initialSpeed)
  speed = travelledDistance / elapsedTimeInSecond;

}

void Kart::moveForward()
{
  //uniteOpenGL / seconde
  currentAcceleration = specifications.acceleration;
}

void Kart::moveBackward()
{
  //uniteOpenGL / seconde
  currentAcceleration = - specifications.acceleration;
}

void Kart::turnLeft()
{
  currentAngularSpeed = specifications.angularSpeed;
}

void Kart::turnRight()
{
  currentAngularSpeed = -specifications.angularSpeed;
}

void Kart::stopMoving()
{
  speed = 0.f;
  currentAcceleration = 0.f;
}

void Kart::stopTurning()
{
  currentAngularSpeed = 0.f;
}

const glm::vec3& Kart::getPosition() const
  {return position;}

const glm::quat& Kart::getOrientation() const
{return orientation;}

