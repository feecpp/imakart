#include "GameEngine.hpp"
#include "Kart.hpp"

GameEngine::GameEngine()
    : state (IN_MENU), player(nullptr), map(nullptr)
{
  //En attendant une gestion plus propre
  player = new Player(hangar.getPlayerKart());
  map = new Map();
  //Je pense que c'est très con de le mettre là, faut que je réfléchisse
  map->loadData("../../imakart/application/maps/carte1.map");
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

Map& GameEngine::getMap() const
{
  //Pas mal de taff encore sur la gestion propre de la création du Player, des Karts...
  assert(map != nullptr);
  return *map;
}

