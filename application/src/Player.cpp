#include "Player.hpp"
#include "Kart.hpp"

Player::Player(Kart& kart)
  :myKart(kart)
{
}

const Kart& Player::getKart() const
{
  return myKart;
}

void Player::moveForward() const
{
  myKart.moveForward();
}

void Player::moveBackward() const
{
  myKart.moveBackward();
}

void Player::turnLeft() const
{
  myKart.turnLeft();
}

void Player::turnRight() const
{
  myKart.turnRight();
}

void Player::stopMoving() const
{
  myKart.stopMoving();
}

void Player::stopTurning() const
{
  myKart.stopTurning();
}

void Player::brake() const
{
  myKart.brake();
}



