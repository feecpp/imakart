#include "RaceEventHandler.hpp"
#include "GameEngine.hpp"

RaceEventHandler::RaceEventHandler(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine)
{
}

void RaceEventHandler::up() const
{
  gameEngine.getPlayer().getKart().moveForward();
}


void RaceEventHandler::down() const
{
  gameEngine.getPlayer().getKart().moveBackward();
}

void RaceEventHandler::left() const
{
  gameEngine.getPlayer().getKart().turnLeft();
}

void RaceEventHandler::right() const
{
  gameEngine.getPlayer().getKart().turnRight();
}

void RaceEventHandler::enter() const
{
	
}
