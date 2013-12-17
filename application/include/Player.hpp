#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Camera.hpp"

class Kart;

class Player
{
public:
  explicit Player(Kart& kart);

  const Kart& getKart() const;
  Kart& getKart();

  void setKart(Kart& myNewKart);

  void moveForward() const;
  void moveBackward() const;
  void turnLeft() const;
  void turnRight() const;
  void stopMoveForward() const;
  void stopMoveBackward() const;
  void stopTurning() const;
  void brake() const;
  void drift() const;

private:
  Kart& myKart;
};

#endif // PLAYER_HPP
