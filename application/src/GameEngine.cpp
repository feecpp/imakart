#include "GameEngine.hpp"
#include "Kart.hpp"
#include <iostream>

GameEngine::GameEngine()
  : state (IN_MENU), player(nullptr), map(nullptr), chrono(nullptr), exitFlag(false), lag(0.f)
{
  chrono = new ChronoLogic();
}

GameEngine::~GameEngine()
{
  delete player;
  delete map;
  delete chrono;
}

void GameEngine::init()
{
  clock.restart();
}

void GameEngine::update()
{
  float elapsedTime = clock.restart().asMilliseconds();
  lag += elapsedTime;

  //Mettre à jour les objets de la simulation ici (en fonction du temps)
  //Cette partie a vraiment besoin qu'on réfléchisse sur l'archi du Game Engine!

  while (lag >= TURN_DURATION_IN_MILLIS)
  {
    if(state != IN_RACE)
    {
      chrono->update(0.f);
    }
    else
    {
      //Uniformiser la gestion du temps
      getPlayerKart().update(TURN_DURATION_IN_MILLIS / 1000.f);
      chrono->update(TURN_DURATION_IN_MILLIS / 1000.f);
    }

    lag -= TURN_DURATION_IN_MILLIS;
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
