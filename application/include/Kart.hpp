#ifndef KART_HPP
#define KART_HPP

#include "Positionable.hpp"
#include "KartEnumerations.hpp"

class Kart : public Positionable
{
public:
  Kart();
  Kart(glm::vec3 position, glm::quat direction, float speed);

  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();

  virtual const glm::vec3& getPosition() const;
  virtual const glm::quat& getOrientation() const;
  const KartState getState() const
    {return state;}

  void setState(KartState newState)
    {state = newState;}


private:
  glm::vec3 position;
  glm::quat orientation;
  float directionAngle;
  float speed;
  KartState state;
};

#endif
