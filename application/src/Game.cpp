#include "Game.hpp"

Game::Game()
  : raceEventHandler(this){
  state = IN_MENU;
}

void Game::init()
{
  //Charger les données du jeu
}

void Game::update()
{
  //Quand il faudra gérer les IA...
}



void Game::quit()
{
  //Quitter le jeu et désallouer les ressources
}

const EventHandler& Game::getHandler()
{
  //En fonction de l'état actuel du jeu, renvoyer le bon handler
  return raceEventHandler;
}
