#include "Player.hpp"
#include "Kart.hpp"
#include <iostream>

Player::Player(Kart& kart)
  :myKart(kart)
{
}

const Kart& Player::getKart() const
{
  return myKart;
}

Kart& Player::getKart()
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

void Player::stopMove() const
{
  myKart.stopMove();
}

void Player::stopTurning() const
{
  myKart.stopTurning();
}

void Player::brake() const
{
  myKart.brake();
}

void Player::drift() const
{
  myKart.drift();
}



