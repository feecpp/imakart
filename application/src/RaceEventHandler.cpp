#include "RaceEventHandler.hpp"
#include "GameEngine.hpp"

RaceEventHandler::RaceEventHandler(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine)
{
}

void RaceEventHandler::pressUp() const
{
  gameEngine.getPlayer().moveForward();

}
void RaceEventHandler::releaseUp() const
{
  gameEngine.getPlayer().stopMoving();
}

void RaceEventHandler::pressDown() const
{
  gameEngine.getPlayer().moveBackward();
}
void RaceEventHandler::releaseDown() const
{
  gameEngine.getPlayer().stopMoving();
}

void RaceEventHandler::pressLeft() const
{
  gameEngine.getPlayer().turnLeft();
}
void RaceEventHandler::releaseLeft() const
{
  gameEngine.getPlayer().stopTurning();
}

void RaceEventHandler::pressRight() const
{
  gameEngine.getPlayer().turnRight();
}
void RaceEventHandler::releaseRight() const
{
  gameEngine.getPlayer().stopTurning();
}

bool RaceEventHandler::pressEnter() const
{	
  return false;
}
void RaceEventHandler::releaseEnter() const
{
}
