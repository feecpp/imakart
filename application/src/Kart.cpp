#include "Kart.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <SFML/System.hpp>
#include <iostream>

Kart::Kart()
    : position(0.f, 0.f, 0.f), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))),
      directionAngle(0.f), speed(0.f), angularSpeed(0.f)
{
}

Kart::Kart(glm::vec3 position, glm::quat orientation, float speed)
  : position(position), orientation(orientation), speed(speed)
{
}

Kart::~Kart()
{
}

void Kart::update()
{
  //Gestion du temps avec Clock de sfml
  sf::Clock Clock;
  sf::Time ElapsedTime = Clock.getElapsedTime();
  float time_sec = ElapsedTime.asSeconds();//Renvoie le temps en seconde sous forme de float
  Clock.restart();

  //Calcul de la nouvelle direction en fonction de l'angularSpeed
  if (speed != 0.f)
  {
    directionAngle += angularSpeed *(time_sec*100000); //ajouter gestion temps
  }
  orientation = glm::angleAxis(directionAngle, glm::vec3(0.f, 1.f, 0.f));

  const glm::vec3 initialDirection = glm::vec3(0.f, 0.f, -1.f);
  glm::vec3 direction = glm::normalize(glm::toMat3(orientation) * initialDirection);

  //Calcul de la nouvelle position en fonction de la speed et de la direction

  // position += direction * speed;//sans la gestion temps
  position += direction * (speed*(time_sec*100000));

}

void Kart::moveForward(){
  speed = 0.1f;
}

void Kart::moveBackward(){
  speed = -0.1f;
}

void Kart::turnLeft(){
  angularSpeed = 10.f;
}

void Kart::turnRight(){
  angularSpeed = -10.f;
}

void Kart::stopMoving()
{
  speed = 0.f;
}

void Kart::stopTurning()
{
  angularSpeed = 0.f;
}

const glm::vec3& Kart::getPosition() const
  {return position;}

const glm::quat& Kart::getOrientation() const
{return orientation;}

