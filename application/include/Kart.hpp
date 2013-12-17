#ifndef KART_HPP
#define KART_HPP

#include "Positionable.hpp"
#include <string>

/**
 * @brief The Kart class
 * Gere le deplacement du Kart d'un point de vue physique.
 * Les unites sont le uniteOGL/seconde et le degre/seconde.
 * Les specifications contiennent les caracteristiques du Kart
 * (vitesse max, acceleration si on choisit qu'elle est constante, vitesse angulaire etc)
 * alors que le Kart en lui meme sauvegarde son etat "en cours" (vitesse actuelle, vitesse angulaire
 * actuelle etc) qui evolue au fil du temps.
 */
class Kart : public Positionable
{
public:

  //Indique si le Kart est actuellement en phase d'acceleration ou de deceleration
  enum AccelerationState
  {
    ACCELERATE,
    DECELERATE,
    BRAKE,
    MAX_SPEED_REACHED,
    DO_NOT_MOVE
  };

  //Indique si le kart est en marche arrière ou nom 
  enum MoveState
  {
    FORWARD,
    BACKWARD,
    NONE
  };

  enum TurnState
  {
    LEFT,
    RIGHT,
    NOTURN
  };

  //Structure qui empacte les caractéristiques du Kart
  struct Specifications
  {
    Specifications()
      : acceleration(4.f), maxSpeed(20.f), angularSpeed(90.f), breakingCoefficient(1.5f), weight(2) {}

    ///Doit etre positive
    float acceleration;
    ///Doit etre positive
    float maxSpeed;
    ///Doit etre positive
    float angularSpeed;
    ///Doit etre positif
    float breakingCoefficient;
    ///Doit être positif
    unsigned int weight;
  };

  Kart();
  Kart(std::string);
  Kart(glm::vec3 position, glm::quat direction, float speed);
  virtual ~Kart();

  //Met à jour le Kart en fonction des ordres qui lui ont été donnés
  void update(float elapsedTimeInSecond);

  //Donne les ordres au Kart
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void stopMoveForward();
  void stopMoveBackward();
  void stopTurning();
  void brake();
  void drift();

  virtual const glm::vec3& getPosition() const;
  virtual const glm::quat& getOrientation() const;

  std::string getName() const
    {return name;}

  MoveState getMoveState() const{
    return moveState;
  }

private:
  glm::vec3 position;
  glm::quat orientation;
  float directionAngle;
  ///La vitesse actuelle en uniteOpenGL/seconde
  float speed;
  ///La vitesse angulaire actuelle en degres/seconde
  float currentAngularSpeed;
  float currentAcceleration;
  AccelerationState accelerationState;
  MoveState moveState;
  TurnState turnState;
  Specifications specifications;
  std::string name;

};

#endif
