#include "Opponent.hpp"
#include "Kart.hpp"
#include <iostream>

Opponent::Opponent(Kart& kart)
  :opponentKart(kart)
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

void Opponent::fillCheckpoints(const std::vector<Checkpoint> checkpoints)
{
  this->checkpoints = checkpoints;
}

void Opponent::validateCheckpoints()
{
  unsigned int cpt = 0;
  for (auto it = checkpoints.begin(); it != checkpoints.end(); ++it)
  {
    if (it->contains(opponentKart.getPosition()))
    {
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
    cpt++;
  }
  cpt = 0;
}

void Opponent::startMovement(){
   opponentKart.moveForward();
   opponentKart.turnLeft();
}



