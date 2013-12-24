#ifndef KARTSTATE_HPP
#define KARTSTATE_HPP

#include "Kart.hpp"

//Classe amie de Kart pour pas se faire chier (acces aux attributs prives)
class KartState
{
public:
  KartState(Kart& kart)
    : kart(kart) {}
  virtual ~KartState() {}


  virtual void start() = 0;
  virtual void update(float elapsedTimeInSecond) = 0;
  virtual void moveForward() = 0;
  virtual void moveBackward() = 0;
  virtual void turnLeft() = 0;
  virtual void turnRight() = 0;
  virtual void stopMove() = 0;

  //Implem par defaut
  virtual void stopTurning()
  {
    kart.currentAngularSpeed = 0.f;
  }

  //Implem par defaut
  virtual void bounce()
  {
    kart.setState(kart.bounceState);
  }

  virtual void brake() = 0;
  virtual void drift() = 0;

protected:
  //C'est souvent ce code la qui revient
  inline glm::vec3 setKartOrientationAndComputeDirection(float elapsedTimeInSecond)
  {
    kart.directionAngle += kart.currentAngularSpeed * (elapsedTimeInSecond); //en degres/secondes
    kart.orientation = glm::angleAxis(kart.directionAngle, glm::vec3(0.f, 1.f, 0.f));

    const glm::vec3 initialDirection = glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 direction = glm::normalize(glm::toMat3(kart.orientation) * initialDirection);
    return direction;
  }

  Kart& kart;

};

//Classe intermediaire pour unir le code d'acceleration qui est commun a toutes les formes d'acceleration
class Acceleration : public KartState
{
public:
  Acceleration(Kart& kart)
    : KartState(kart) {}
  virtual ~Acceleration() {}

  virtual void update(float elapsedTimeInSecond)
  {
    glm::vec3 direction = setKartOrientationAndComputeDirection(elapsedTimeInSecond);

    float travelledDistance = kart.speed * elapsedTimeInSecond + kart.currentAcceleration * (elapsedTimeInSecond * elapsedTimeInSecond) / 2.f;
    kart.position += direction * travelledDistance;

    kart.speed = travelledDistance / elapsedTimeInSecond;

    if (kart.speed >= kart.specifications.maxSpeed)
    {
      setMaxSpeedState();//définie par les classes filles
    }
  }

  virtual void setMaxSpeedState() = 0;

  virtual void brake()
  {
    kart.currentAcceleration = - kart.specifications.breakingCoefficient * kart.currentAcceleration;
  }

};

class ForwardAcceleration : public Acceleration
{
public:
  ForwardAcceleration(Kart& kart)
    : Acceleration(kart) {}

  //Pas besoin de redéfinir update !
  virtual void setMaxSpeedState()
  {
    kart.setState(kart.forwardMaxSpeedReached);
  }

  virtual void start()
  {
    kart.currentAcceleration = kart.specifications.acceleration;
  }

  virtual void moveForward()
  {
    //J'y suis deja et pour l'instant est considere constante donc je fais rien !
  }

  virtual void moveBackward()
  {
    brake();
    kart.setState(kart.backwardAccelerationState);
  }

  virtual void turnLeft()
  {
    kart.currentAngularSpeed = kart.specifications.angularSpeed;
  }

  virtual void turnRight()
  {
    kart.currentAngularSpeed = - kart.specifications.angularSpeed;
  }

  virtual void stopMove()
  {
    kart.setState(kart.forwardDecelerationState);
  }

  void drift()
  {
    //TODO
  }
};

///Le seul truc qui change par rapport a la classe mere, c'est update !
class ForwardMaxSpeedReached : public ForwardAcceleration //Tada !
{
public:
  ForwardMaxSpeedReached(Kart& kart)
    : ForwardAcceleration(kart) {}

  virtual void update(float elapsedTimeInSecond)
  {
    glm::vec3 direction = setKartOrientationAndComputeDirection(elapsedTimeInSecond);

    //Seul changement : cette ligne !
    float travelledDistance = kart.specifications.maxSpeed * elapsedTimeInSecond;
    kart.position += direction * travelledDistance;
  }
};

class BackwardAcceleration : public Acceleration
{
public:
  BackwardAcceleration(Kart& kart)
    : Acceleration(kart) {}

  //Pas besoin de redéfinir update !
  virtual void setMaxSpeedState()
  {
    kart.setState(kart.backwardMaxSpeedReached);
  }

  virtual void start()
  {
      kart.currentAcceleration = -kart.specifications.acceleration;
  }

  virtual void moveForward()
  {
    brake();
    kart.setState(kart.forwardAccelerationState);
  }

  virtual void moveBackward()
  {
    //cf ForwardAccelerationState
  }

  virtual void turnLeft()
  {
    kart.currentAngularSpeed = -kart.specifications.angularSpeed;
  }

  virtual void turnRight()
  {
    kart.currentAngularSpeed = kart.specifications.angularSpeed;
  }

  virtual void stopMove()
  {
    kart.setState(kart.backwardDecelerationState);
  }

  void drift()
  {
    //TODO
  }
};

class BackwardMaxSpeedReached : public BackwardAcceleration
{
public:
  BackwardMaxSpeedReached(Kart& kart)
    : BackwardAcceleration(kart) {}

  virtual void update(float elapsedTimeInSecond)
  {
    glm::vec3 direction = setKartOrientationAndComputeDirection(elapsedTimeInSecond);

    //Seul changement : cette ligne ! (diff par rapport a la forward : le moins devant maxspeed)
    float travelledDistance = - kart.specifications.maxSpeed * elapsedTimeInSecond;
    kart.position += direction * travelledDistance;

  }
};


class Deceleration : public KartState
{
public:
  Deceleration(Kart& kart)
    : KartState(kart) {}
  virtual ~Deceleration() {}

  //On se permet de regrouper l'update car les state sont supposes s'appeler dans le bon ordre,
  //Donc la valeur de kart.currentAcceleration devrait toujours etre bonne quand on arrive ici
  virtual void update(float elapsedTimeInSecond)
  {
    glm::vec3 direction = setKartOrientationAndComputeDirection(elapsedTimeInSecond);
    //Attention ici au moins : nous sommes en phase de deceleration
    float travelledDistance = kart.speed * elapsedTimeInSecond + kart.currentAcceleration * (elapsedTimeInSecond * elapsedTimeInSecond) / 2.f;
    float supposedNewSpeed = travelledDistance / elapsedTimeInSecond;
    if (abs(kart.speed - 0.f) <= 0.000001f || supposedNewSpeed / kart.speed < 0.f)
    {
      kart.setState(kart.noMoveState);
    }
    else
    {
      kart.speed = supposedNewSpeed;
    }

    kart.position += direction * travelledDistance;
  }

  //Le freinage aussi est commun
  virtual void brake()
  {
    kart.currentAcceleration = kart.specifications.breakingCoefficient * kart.currentAcceleration;
  }

};

class ForwardDeceleration : public Deceleration
{
public:
  ForwardDeceleration(Kart& kart)
    : Deceleration(kart) {}

  virtual void start()
  {
    kart.currentAcceleration = -kart.currentAcceleration;
  }

  virtual void moveForward()
  {
    kart.setState(kart.forwardAccelerationState);
  }

  virtual void moveBackward()
  {
    brake();
    kart.setState(kart.backwardAccelerationState);
  }

  virtual void turnLeft()
  {
    kart.currentAngularSpeed = kart.specifications.angularSpeed;
  }

  virtual void turnRight()
  {
    kart.currentAngularSpeed = -kart.specifications.angularSpeed;
  }

  virtual void stopMove()
  {
    //What the fuck am I doing here ?? :p
  }

  void drift()
  {
    //TODO
  }

};

class BackwardDeceleration : public Deceleration
{
public:

  BackwardDeceleration(Kart& kart)
    : Deceleration(kart) {}

  virtual void start()
  {
    kart.currentAcceleration = -kart.currentAcceleration;
  }

  virtual void moveForward()
  {
    brake();
    kart.setState(kart.forwardAccelerationState);
  }

  virtual void moveBackward()
  {
    kart.setState(kart.backwardAccelerationState);
  }

  virtual void turnLeft()
  {
    kart.currentAngularSpeed = -kart.specifications.angularSpeed;
  }

  virtual void turnRight()
  {
    kart.currentAngularSpeed = kart.specifications.angularSpeed;
  }

  virtual void stopMove()
  {
    //What the fuck am I doing here ?? :p
  }

  virtual void drift()
  {
    //TODO
  }
};

//Etat qui fait rien a part changer d'etat
class NoMove : public KartState
{
public:
  NoMove(Kart& kart)
    : KartState(kart) {}

  virtual void start()
  {
    kart.speed = 0.f;
    kart.currentAcceleration = 0.f;
  }

  virtual void update(float elapsedTimeInSecond) {}

  virtual void moveForward()
  {
    kart.setState(kart.forwardAccelerationState);
  }

  virtual void moveBackward()
  {
    kart.setState(kart.backwardAccelerationState);
  }

  //On peut pas bouncer immobile
  virtual void bounce() {}
  virtual void turnLeft() {}
  virtual void turnRight() {}
  virtual void stopMove() {}
  virtual void brake() {}
  virtual void drift() {}
};

class Bounce : public KartState
{
public:
  Bounce(Kart& kart)
    : KartState(kart), distanceToTravel(3.f), currentDistance(0.f), bouncing(false) {}

  virtual void start()
  {
    //Si on est deja en train de bouncer on reinitialise pas
    if (bouncing)
      return;

    currentDistance = 0.f;
    distanceToTravel = log(abs(kart.speed)) - 0.5f;//au hasard
    kart.speed = -kart.speed;
    bouncing = true;
  }

  virtual void update(float elapsedTimeInSecond)
  {
    if (abs(currentDistance) >= distanceToTravel)
    {
      kart.setState(kart.noMoveState);
      //Se remet a zero
      bouncing = false;
      return;
    }

    glm::vec3 direction = setKartOrientationAndComputeDirection(elapsedTimeInSecond);
    float travelledDistance = kart.speed * elapsedTimeInSecond + kart.currentAcceleration * (elapsedTimeInSecond * elapsedTimeInSecond) / 2.f;
    kart.speed = travelledDistance / elapsedTimeInSecond;
    kart.position += direction * travelledDistance;
    currentDistance = currentDistance + travelledDistance;
  }

  //Redefinition, TODO y'a ptete un truc mieux a faire
  virtual void bounce() {}

  virtual void moveBackward() {}
  virtual void moveForward() {}
  virtual void turnLeft(){}
  virtual void turnRight() {}
  virtual void stopMove() {}
  virtual void brake() {}
  virtual void drift() {}

private:
  ///La distance parcourue pendant un bounce
  float distanceToTravel;
  double currentDistance;
  bool bouncing;

};

#endif // KARTSTATE_HPP
