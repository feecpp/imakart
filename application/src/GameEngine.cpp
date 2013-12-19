#include "GameEngine.hpp"
#include "Kart.hpp"
#include <iostream>

GameEngine::GameEngine()
  : state (IN_MENU), player(nullptr), map(nullptr), chrono(nullptr), exitFlag(false)
{
  chrono = new ChronoLogic();
}

void GameEngine::init()
{
  clock.restart();
}

void GameEngine::update()
{
  float elapsedTime = clock.restart().asSeconds();
  //Mettre à jour les objets de la simulation ici (en fonction du temps)
  //Cette partie a vraiment besoin qu'on réfléchisse sur l'archi du Game Engine!

  if(state != IN_RACE)
  {
    chrono->update(0.f);
  }
  else
  {
    //Le player n'existe pas si pas IN_RACE
    getPlayerKart().update(elapsedTime);
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

void GameEngine::setupPlayer(const std::string& playerKartName)
{
  player = new Player(hangar.createKartInstanceByName(playerKartName));
}


Player& GameEngine::getPlayer() const
{
  //Pas mal de taff encore sur la gestion propre de la création du Player, des Karts...
  assert(player != nullptr);
  return *player;
}

Kart& GameEngine::getPlayerKart() const
{
  assert(player != nullptr);
  return player->getKart();
}

Map& GameEngine::getMap() const
{
  assert(map != nullptr);
  return *map;
}

ChronoLogic& GameEngine::getChrono() const
{
  return *chrono;
}
