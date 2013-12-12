#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Camera.hpp"

class Kart;

class Player
{
public:
  explicit Player(Kart& kart);

  const Kart& getKart() const;

  void moveForward() const;
  void moveBackward() const;
  void turnLeft() const;
  void turnRight() const;
  void stopMoving() const;
  void stopTurning() const;
  void brake() const;

private:
  Kart& myKart;
};

#endif // PLAYER_HPP
