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

void Player::moveForward()
{
  myKart.moveForward();
}

void Player::moveBackward()
{
  myKart.moveBackward();
}

void Player::turnLeft()
{
  myKart.turnLeft();
}

void Player::turnRight()
{
  myKart.turnRight();
}

void Player::stopMoving()
{
  myKart.stopMoving();
}

void Player::stopTurning()
{
  myKart.stopTurning();
}



