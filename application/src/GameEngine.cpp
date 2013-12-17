#include "GameEngine.hpp"
#include "Kart.hpp"
#include <iostream>

GameEngine::GameEngine()
  : state (IN_MENU), player(nullptr), map(nullptr), chrono(nullptr), exitFlag(false)
{
  //En attendant une gestion plus propre
  player = new Player(hangar.getPlayerKart());
  map = new Map();
  //Je pense que c'est très con de le mettre là, faut que je réfléchisse
  map->loadData("../../imakart/application/maps/carte1.map");
  chrono = new Chrono();
}

void GameEngine::init()
{
  clock.restart();
}

void GameEngine::update()
{
  float elapsedTime = clock.restart().asSeconds();
  //Mettre à jour les objets de la simulation ici (en fonction du temps)
  hangar.getPlayerKart().update(elapsedTime);

  if(state != IN_RACE){
    chrono->update(0.f);
  }else{
    chrono->update(elapsedTime);
  }


}

void GameEngine::activateExitFlag()
{
  exitFlag = true;
}

void GameEngine::deactivateExitFlag()
{
  exitFlag = false;
}

bool GameEngine::getExitFlag() const
{
  return exitFlag;
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

Chrono& GameEngine::getChrono() const
{
  return *chrono;
}
