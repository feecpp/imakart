#include "MenuEventHandler.hpp"
#include "GameEngine.hpp"
#include <iostream>

MenuEventHandler::MenuEventHandler(GameEngine* gameEngine)
  : gameEngine(gameEngine)
{
}

void MenuEventHandler::up() const
{
	gameEngine->getMenuLogic().previousButton();
}


void MenuEventHandler::down() const
{
	gameEngine->getMenuLogic().nextButton();
}

void MenuEventHandler::left() const
{
	
}

void MenuEventHandler::right() const
{

}

