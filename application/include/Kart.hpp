#ifndef KART_HPP
#define KART_HPP

#include "Positionable.hpp"

class Kart : public Positionable
{
public:
  Kart();
  Kart(glm::vec3 position, glm::quat direction, float speed);
  virtual ~Kart();

  //Met à jour le Kart en fonction des ordres qui lui ont été donnés
  void update();

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
  float speed;
  float angularSpeed;
  float lastTimeIMoved;
};

#endif
