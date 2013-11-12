#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Camera.hpp"

class Kart;

class Player
{
public:
  explicit Player(Kart& kart);

  const Kart& getKart() const;

  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void stopMoving();
  void stopTurning();

private:
  Kart& myKart;
};

#endif // PLAYER_HPP
