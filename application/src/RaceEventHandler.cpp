#include "RaceEventHandler.hpp"
#include "GameEngine.hpp"

RaceEventHandler::RaceEventHandler(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine)
{
}

void RaceEventHandler::pressUp() const
{
  gameEngine.getPlayer().getKart().setState(MOVE_FORWARD);

}
void RaceEventHandler::releaseUp() const
{
    gameEngine.getPlayer().getKart().setState(REST_STATE);
}

void RaceEventHandler::pressDown() const
{
  gameEngine.getPlayer().getKart().setState(MOVE_BACKWARD);
}
void RaceEventHandler::releaseDown() const
{
  gameEngine.getPlayer().getKart().setState(REST_STATE);
}

void RaceEventHandler::pressLeft() const
{
  gameEngine.getPlayer().getKart().setState(TURN_LEFT);
}
void RaceEventHandler::releaseLeft() const
{
  gameEngine.getPlayer().getKart().setState(REST_STATE);
}

void RaceEventHandler::pressRight() const
{
  gameEngine.getPlayer().getKart().setState(TURN_RIGHT);
}
void RaceEventHandler::releaseRight() const
{
  gameEngine.getPlayer().getKart().setState(REST_STATE);
}

void RaceEventHandler::pressEnter() const
{	
}
void RaceEventHandler::releaseEnter() const
{
}
