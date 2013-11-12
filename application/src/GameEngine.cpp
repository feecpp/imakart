#include "GameEngine.hpp"
#include "Kart.hpp"

GameEngine::GameEngine()
  : state (IN_MENU), player(nullptr)
{
  //En attendant une gestion plus propre
  player = new Player(hangar.getPlayerKart());
}

void GameEngine::init()
{

}

void GameEngine::update()
{
  hangar.getPlayerKart().update();
}


Player& GameEngine::getPlayer() const
{
  //Pas mal de taff encore sur la gestion propre de la création du Player, des Karts...
  assert(player != nullptr);
  return *player;
}

Kart& GameEngine::getPlayerKart() const
{
  return hangar.getPlayerKart();
}

