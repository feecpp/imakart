#include "GameEngine.hpp"

GameEngine::GameEngine()
  : raceEventHandler(this){
  state = IN_MENU;
}

void GameEngine::init()
{
  //Charger les données du jeu
}

void GameEngine::update()
{
  //Quand il faudra gérer les IA...
}



void GameEngine::quit()
{
  //Quitter le jeu et désallouer les ressources
}

const EventHandler& GameEngine::getHandler() const
{
  //En fonction de l'état actuel du jeu, renvoyer le bon handler
  return raceEventHandler;
}
