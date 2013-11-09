#include "MenuEventHandler.hpp"
#include "GameEngine.hpp"
#include <iostream>

MenuEventHandler::MenuEventHandler(GameEngine& gameEngine)
  : gameEngine(gameEngine)
{
}

void MenuEventHandler::pressUp() const
{
  gameEngine.getMenuLogic().previousButton();
}
void MenuEventHandler::releaseUp() const
{
}

void MenuEventHandler::pressDown() const
{
  gameEngine.getMenuLogic().nextButton();
}
void MenuEventHandler::releaseDown() const
{
}

void MenuEventHandler::pressLeft() const
{	
}
void MenuEventHandler::releaseLeft() const
{
}

void MenuEventHandler::pressRight() const
{

}
void MenuEventHandler::releaseRight() const
{

}

void MenuEventHandler::pressEnter() const
{
	gameEngine.getMenuLogic().submitButton();
}
void MenuEventHandler::releaseEnter() const
{

}

