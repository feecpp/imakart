#ifndef KART_HPP
#define KART_HPP

#include "Positionable.hpp"
#include <string>
#include "BoundingBox.hpp"

class KartState;
class ForwardAcceleration;
class BackwardAcceleration;
class ForwardDeceleration;
class BackwardDeceleration;
class ForwardMaxSpeedReached;
class BackwardMaxSpeedReached;
class Acceleration;
class Deceleration;
class NoMove;

/**
 * @brief The Kart class
 * Gere le deplacement du Kart d'un point de vue physique.
 * Les unites sont le uniteOGL/seconde et le degre/seconde.
 * Les specifications contiennent les caracteristiques du Kart
 * (vitesse max, acceleration si on choisit qu'elle est constante, vitesse angulaire etc)
 * alors que le Kart en lui meme sauvegarde son etat "en cours" (vitesse actuelle, vitesse angulaire
 * actuelle etc) qui evolue au fil du temps.
 */

struct Specifications
 {
  Specifications()
    : acceleration(4.f), maxSpeed(20.f), angularSpeed(90.f), breakingCoefficient(6.0f), weight(2) {}

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

class Kart : public Positionable
{
public:

  //Structure qui empacte les caractéristiques du Kart

  Kart();
  Kart(std::string kartName);
  Kart(glm::vec3 position, glm::quat direction, float speed);

  explicit Kart(const Kart& kartToCopy);

  virtual ~Kart();

  //Met à jour le Kart en fonction des ordres qui lui ont été donnés
  void update(float elapsedTimeInSecond);

  //Donne les ordres au Kart
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void stopMove();
  void stopTurning();
  void brake();
  void drift();
  void bounce();
  void boost();

  virtual const glm::vec3& getPosition() const;
  void setPosition(glm::vec3 pos);
  virtual const glm::quat& getOrientation() const;

  std::string getName() const
    {return name;}

  const BoundingBox& getBoundingBox() const
    {return boundingBox;}

  const float* getCurrentSpeed() const
    {return &speed; }

Specifications specifications;
private:
  void initStates();
  //Ouais,c'est un peu sale, mais j'ai pas trouve plus simple pour l'instant
  //On pourrait foutre des getters/setters mais ca veut dire que Kart devien OpenBar
  friend class KartState;
  friend class ForwardAcceleration;
  friend class BackwardAcceleration;
  friend class ForwardDeceleration;
  friend class BackwardDeceleration;
  friend class ForwardMaxSpeedReached;
  friend class BackwardMaxSpeedReached;
  friend class Acceleration;
  friend class Deceleration;
  friend class NoMove;
  friend class Bounce;
  friend class Boost;
  friend class ForwardBrake;
  friend class BackwardBrake;

  void setState(KartState* newState);

  glm::vec3 BOUNDING_BOX_SIZE;

  glm::vec3 position;
  BoundingBox boundingBox;
  glm::quat orientation;
  float directionAngle;
  ///La vitesse actuelle en uniteOpenGL/seconde
  float speed;
  ///La vitesse angulaire actuelle en degres/seconde
  float currentAngularSpeed;
  float currentAcceleration;

  std::string name;

  KartState* forwardAccelerationState;
  KartState* forwardDecelerationState;
  KartState* forwardMaxSpeedReached;
  KartState* backwardAccelerationState;
  KartState* backwardDecelerationState;
  KartState* backwardMaxSpeedReached;
  KartState* noMoveState;
  KartState* bounceState;
  KartState* boostState;
  KartState* forwardBrakeState;
  KartState* backwardBrakeState;
  KartState* currentState;

};

#endif
