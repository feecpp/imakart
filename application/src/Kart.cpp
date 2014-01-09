#include "Kart.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <SFML/System.hpp>
#include <ObjectFile.hpp>
#include <iostream>
#include "KartState.hpp"

/////// Site qui a l'air pratique pour la physique : http://www.formules-physique.com/categorie/687 //////////////

void Kart::initStates()
{
  forwardAccelerationState = new ForwardAcceleration(*this);
  forwardDecelerationState = new ForwardDeceleration(*this);
  forwardMaxSpeedReached = new ForwardMaxSpeedReached(*this);
  backwardAccelerationState = new BackwardAcceleration(*this);
  backwardDecelerationState = new BackwardDeceleration(*this);
  backwardMaxSpeedReached = new BackwardMaxSpeedReached(*this);
  noMoveState = new NoMove(*this);
  bumpedState = new Bumped(*this);
  bounceState = new Bounce(*this);
  boostState = new Boost(*this);
  forwardBrakeState = new ForwardBrake(*this);
  backwardBrakeState = new BackwardBrake(*this);
  currentState = noMoveState;
}

Kart::Kart()
  : BOUNDING_BOX_SIZE(glm::vec3(3.f)), position(0.f, 0.f, 0.f), boundingBox(position, BOUNDING_BOX_SIZE), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))),
    directionAngle(0.f), speed(0.f), currentAngularSpeed(0.f), currentAcceleration(0.f), name("standard"), eventStack(nullptr)
{
  initStates();
}

Kart::Kart(std::string kartName)
  : BOUNDING_BOX_SIZE(glm::vec3(3.f)), position(1.9f, 0.f, 6.f), boundingBox(position, BOUNDING_BOX_SIZE), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))),
      directionAngle(0.f), speed(0.f), currentAngularSpeed(0.f), currentAcceleration(0.f), eventStack(nullptr)
{
  const std::string path = "karts/"+kartName+".kart";

  //Je crée un ObjectFile à partir du fichier.kart et récupère un std::map
  ObjectFile kartFile(path);
  std::map<std::string, std::string> map = kartFile.getData();

  //Mise a jour des specs à partir de la std::map
  name = map["Name"];
  specifications.acceleration = (float)(atoi(map["Acceleration"].c_str()));
  specifications.maxSpeed = (float)(atoi(map["MaxSpeed"].c_str()));
  specifications.weight = atoi(map["Weight"].c_str());

  initStates();
}

Kart::Kart(const Kart& kartToCopy)
  : specifications(kartToCopy.specifications), position(kartToCopy.position), boundingBox(kartToCopy.boundingBox), orientation(kartToCopy.orientation), directionAngle(0.f), speed(kartToCopy.speed),
    currentAngularSpeed(0.f), currentAcceleration(0.f), name(kartToCopy.name), eventStack(kartToCopy.eventStack)
{
  initStates();
}

Kart::~Kart()
{
  delete forwardAccelerationState;
  delete forwardDecelerationState;
  delete forwardMaxSpeedReached;
  delete backwardAccelerationState;
  delete backwardDecelerationState;
  delete backwardMaxSpeedReached;
  delete noMoveState;
  delete bumpedState;
  delete bounceState;
  delete boostState;
  delete forwardBrakeState;
  delete backwardBrakeState;
  currentState = nullptr;
}

void Kart:: setPosition(glm::vec3 pos){
  position = pos;
}

void Kart::update(float elapsedTimeInSecond)
{
  currentState->update(elapsedTimeInSecond);
  boundingBox.setPosition(position);
}

void Kart::moveForward() //enclenche la marche avant
{
  currentState->moveForward();
}

void Kart::moveBackward() //enclenche la marche arriere
{
  currentState->moveBackward();
}

void Kart::turnLeft()
{
  currentState->turnLeft();
}

void Kart::turnRight()
{
  currentState->turnRight();
}

void Kart::stopMove()
{
  currentState->stopMove();
}

void Kart::bumped()
{
  setState(bumpedState);
}

void Kart::stopTurning()
{
  currentState->stopTurning();
}

//Le freinage est juste une deceleration plus puissante pour l'instant
void Kart::brake()
{
  currentState->brake();
}

void Kart::drift() //Pas encore géré
{
  currentState->drift();
}

void Kart::bounce()
{
  setState(bounceState);
}

void Kart::boost()
{
  setState(boostState);
}

const glm::vec3& Kart::getPosition() const
  {return position;}

const glm::quat& Kart::getOrientation() const
{return orientation;}

void Kart::setEventStack(std::stack<GameEvent>* const eventStack)
{
  this->eventStack = eventStack;
  boostState->setEventStack(eventStack);
  bounceState->setEventStack(eventStack);
}

void Kart::setState(KartState* newState)
{
  newState->start();
  currentState = newState;
}
