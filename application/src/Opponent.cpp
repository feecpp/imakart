#include "Opponent.hpp"
#include "Kart.hpp"
#include <iostream>

Opponent::Opponent(Kart& kart)
  :opponentKart(kart)
{
}

const Kart& Opponent::getKart() const
{
  return opponentKart;
}

Kart& Opponent::getKart()
{
  return opponentKart;
}

void Opponent::startMovement(){
   opponentKart.moveForward();
   opponentKart.turnLeft();
}



