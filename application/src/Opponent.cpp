#include "Opponent.hpp"
#include "Kart.hpp"
#include <iostream>

const unsigned int Opponent::MAX_LAP = 2;

Opponent::Opponent(Kart& kart, std::stack<GameEvent>& eventStack)
  :opponentKart(kart), eventStack(eventStack), currentLap(0), newLapNextTime(false)
{
  checkpoints.resize(0);
}

const Kart& Opponent::getKart() const
{
  return opponentKart;
}

Kart& Opponent::getKart()
{
  return opponentKart;
}

const unsigned int& Opponent::getCurrentLap() const
{
  return currentLap;
}

unsigned int& Opponent::getCurrentLap()
{
  return currentLap;
}

void Opponent::fillCheckpoints(const std::vector<Checkpoint> checkpoints)
{
  this->checkpoints = checkpoints;
}

void Opponent::validateCheckpoints()
{
  bool allChecked = true;
  bool newLap = false;
  unsigned int cpt = 0;
  int nbChecked = 0;
  for (auto it = checkpoints.begin(); it != checkpoints.end(); ++it)
  {
    if (newLapNextTime && !it->start)
      continue;
    if (it->contains(opponentKart.getPosition()))
    {
      it->checked = true;
      if(it->start && (newLapNextTime || currentLap == 0))
        newLap = true;

      //je vais chercher le checkpoint valide
      /*
      std::cout <<"position du checkpoint valide x : "<< it->position.x << std::endl;
      std::cout <<"position du checkpoint valide y : "<< it->position.y << std::endl;
*/
      //je vais chercher le checkpoint suivant
      if(cpt <= checkpoints.size()){
        cpt = 0;
      }
      /*
      std::cout <<"position du checkpoint suivant x : "<< checkpoints[cpt].position.x << std::endl;
      std::cout <<"position du checkpoint suivant y : "<< checkpoints[cpt].position.y << std::endl;
      */
      cpt--;

      // calcul de l'angle

      //actualisation mouvement
    }
    if ( !it->checked)
      allChecked = false;
    else
      nbChecked++;
    cpt++;
  }
  cpt = 0;
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
    //On émet un event nouveau tour
    if (currentLap > Opponent::MAX_LAP)
    {
      eventStack.push(GameEvent(RACE_FINISHED, GameEventData()));
    }
    else
    {
    GameEventData data;
    data.lapNumber = currentLap;
    eventStack.push(GameEvent(NEW_LAP, data));
    }
    newLapNextTime = false;
  }

}

void Opponent::startMovement(){
   opponentKart.moveForward();
   opponentKart.turnLeft();
}



