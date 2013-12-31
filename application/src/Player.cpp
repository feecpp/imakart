#include "Player.hpp"
#include "Kart.hpp"
#include "ItemLogic.hpp"
#include "ItemBox.hpp"
#include <iostream>

Player::Player(Kart& kart)
  :myKart(kart), myCurrentItem(nullptr)
{
  myCurrentItem = ItemBox::getSingletonItemBox()->createItemInstanceByName("Banana");
}

const Kart& Player::getKart() const
{
  return myKart;
}

Kart& Player::getKart()
{
  return myKart;
}

const ItemLogic& Player::getItem() const
{
  return *myCurrentItem;
}

ItemLogic& Player::getItem()
{
  return *myCurrentItem;
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

void Player::setItem(ItemLogic* newItem)
{
  myCurrentItem = newItem;
}

void Player::useItem()
{
  if(myCurrentItem != nullptr){
    if(myCurrentItem->getEffect() == "boost()"){
        myKart.boost();
    }
    
    delete myCurrentItem;
    myCurrentItem = nullptr;
  } 
}