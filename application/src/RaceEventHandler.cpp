#include "RaceEventHandler.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"
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
  if(*(gameEngine.getPlayerKart().getCurrentSpeed()) <= 0){
    graphicEngine.getWorld3D().switchInBackwardView();
    gameEngine.getPlayer().switchInBackwardView();
  }
}
void RaceEventHandler::releaseDown() const
{
  gameEngine.getPlayer().stopMove();

  graphicEngine.getWorld3D().switchInForwardView();
  gameEngine.getPlayer().switchInForwardView();
}

void RaceEventHandler::pressLeft() const
{
  gameEngine.getPlayer().turnLeft();
  graphicEngine.getWorld3D().switchInLeftBendView();
}
void RaceEventHandler::releaseLeft() const
{
  gameEngine.getPlayer().stopTurning();
  graphicEngine.getWorld3D().switchInForwardView();
}

void RaceEventHandler::pressRight() const
{
  gameEngine.getPlayer().turnRight();
  graphicEngine.getWorld3D().switchInRightBendView();
}
void RaceEventHandler::releaseRight() const
{
  gameEngine.getPlayer().stopTurning();
  graphicEngine.getWorld3D().switchInForwardView();
}

void RaceEventHandler::pressEnter() const
{	
  gameEngine.getPlayer().useItem();
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

void RaceEventHandler::pressNumpad0() const
{
  graphicEngine.getWorld3D().switchInBackwardView();
  gameEngine.getPlayer().switchInBackwardView();

}

void RaceEventHandler::releaseNumpad0() const
{
  graphicEngine.getWorld3D().switchInForwardView();
  gameEngine.getPlayer().switchInForwardView();
}

void RaceEventHandler::pressEscape() const
{
  if (gameEngine.getState() == BEFORE_RACE_BEGIN || gameEngine.getState() == END_OF_RACE)
    return;

  gameEngine.setState(IN_RACE_MENU);
  gameEngine.switchPause();
}

void RaceEventHandler::pressK() const
{
  gameEngine.getPlayer().klaxon();
}