#include "ContextManager.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"


ContextManager::ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine), raceEventHandler(gameEngine, graphicEngine),
    menuEventHandler(gameEngine)
{}

void ContextManager::setupMenuContext() const
{

}

void ContextManager::setupRaceContext() const
{

}

const EventHandler& ContextManager::getHandler() const
{
  if (gameEngine.getState() == IN_MENU)
    return menuEventHandler;
  else if (gameEngine.getState() == IN_RACE)
    return raceEventHandler;
  return menuEventHandler;//TODO
}
