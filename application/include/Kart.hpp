#ifndef KART_HPP
#define KART_HPP

#include "Positionable.hpp"

/**
 * @brief The Kart class
 * Gere le deplacement du Kart d'un point de vue physique.
 * Les unites sont le uniteOGL/seconde et le degre/seconde.
 */
class Kart : public Positionable
{
public:
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
  ///La vitesse en uniteOpenGL/seconde
  float speed;
  ///La vitesse angulaire en degres/seconde
  float angularSpeed;
};

#endif
