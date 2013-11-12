#include "RaceEventHandler.hpp"
#include "GameEngine.hpp"

RaceEventHandler::RaceEventHandler(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine)
{
}

void RaceEventHandler::pressUp() const
{
  gameEngine.getPlayer().getKart().moveForward();

}
void RaceEventHandler::releaseUp() const
{
  gameEngine.getPlayer().getKart().stopMoving();
}

void RaceEventHandler::pressDown() const
{
  gameEngine.getPlayer().getKart().moveBackward();
}
void RaceEventHandler::releaseDown() const
{
  gameEngine.getPlayer().getKart().stopMoving();
}

void RaceEventHandler::pressLeft() const
{
  gameEngine.getPlayer().getKart().turnLeft();
}
void RaceEventHandler::releaseLeft() const
{
  gameEngine.getPlayer().getKart().stopTurning();
}

void RaceEventHandler::pressRight() const
{
  gameEngine.getPlayer().getKart().turnRight();
}
void RaceEventHandler::releaseRight() const
{
  gameEngine.getPlayer().getKart().stopTurning();
}

void RaceEventHandler::pressEnter() const
{	
}
void RaceEventHandler::releaseEnter() const
{
}
