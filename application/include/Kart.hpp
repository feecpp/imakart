#ifndef KART_HPP
#define KART_HPP

#include "Positionable.hpp"

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
  //Structure qui empacte les caractéristiques du Kart
  struct Specifications
  {
    Specifications()
      : acceleration(2.f), maxSpeed(20.f), angularSpeed(90.f) {}
    Specifications(float acceleration, float maxSpeed)
      : acceleration(acceleration), maxSpeed(maxSpeed), angularSpeed(90.f) {}

    float acceleration;
    float maxSpeed;
    float angularSpeed;
  };

  Kart();
  Kart(glm::vec3 position, glm::quat direction, float speed);
  virtual ~Kart();

  //Met à jour le Kart en fonction des ordres qui lui ont été donnés
  void update(float elapsedTimeInSecond);

  //Donne les ordres au Kart
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void stopMoving();
  void stopTurning();

  virtual const glm::vec3& getPosition() const;
  virtual const glm::quat& getOrientation() const;

private:
  glm::vec3 position;
  glm::quat orientation;
  float directionAngle;
  ///La vitesse actuelle en uniteOpenGL/seconde
  float speed;
  ///La vitesse angulaire actuelle en degres/seconde
  float currentAngularSpeed;
  float currentAcceleration;
  Specifications specifications;
};

#endif
