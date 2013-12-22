#include "RaceEventHandler.hpp"
#include "GameEngine.hpp"
#include <iostream>

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
  gameEngine.getPlayer().stopMove();
}

void RaceEventHandler::pressDown() const
{
  gameEngine.getPlayer().moveBackward();
}
void RaceEventHandler::releaseDown() const
{
  gameEngine.getPlayer().stopMove();
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

void RaceEventHandler::pressEnter() const
{	

}

void RaceEventHandler::releaseEnter() const
{
}

void RaceEventHandler::pressSpace() const
{
  gameEngine.getPlayer().brake();
}

void RaceEventHandler::releaseSpace() const
{
}
