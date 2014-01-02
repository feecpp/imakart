#include "Player.hpp"
#include "Kart.hpp"
#include "ItemLogic.hpp"
#include "ItemBox.hpp"
#include <iostream>

Player::Player(Kart& kart, std::stack<GameEvent>& eventStack)
  :myKart(kart), eventStack(eventStack), myCurrentItem(nullptr), currentLap(0), newLapNextTime(false)
{
  checkpoints.resize(0);
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

void Player::fillCheckpoints(const std::vector<Checkpoint> checkpoints)
{
  this->checkpoints = checkpoints;
}

#include <iostream>
void Player::validateCheckpoints()
{
  bool allChecked = true;
  bool newLap = false;
  for (auto it = checkpoints.begin(); it != checkpoints.end(); ++it)
  {
    if (it->contains(myKart.getPosition()))
    {
      it->checked = true;
      if(it->start && (newLapNextTime || currentLap == 0))
        newLap = true;
    }
    if ( !it->checked)
      allChecked = false;
  }

  //Si tous les checkpoints sont check : reset
  if (allChecked)
  {
    newLapNextTime = true;
    for (auto it = checkpoints.begin(); it != checkpoints.end(); ++it)
    {
      it->checked = false;
    }
  }

  if (newLap)
  {
    currentLap++;
    std::cerr << "new lap:" << currentLap << std::endl;
    //On émet un event nouveau tour
    GameEventData data;
    data.lapNumber = currentLap;
    eventStack.push(GameEvent(NEW_LAP, data));
    newLapNextTime = false;
  }

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
