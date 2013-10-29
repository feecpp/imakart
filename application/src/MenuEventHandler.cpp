#include "MenuEventHandler.hpp"
#include "GameEngine.hpp"
#include <iostream>

MenuEventHandler::MenuEventHandler(GameEngine* gameEngine)
  : gameEngine(gameEngine)
{
}

void MenuEventHandler::up() const
{
  gameEngine->getMenu().previous_button();
}


void MenuEventHandler::down() const
{
  gameEngine->getMenu().next_button();
}

void MenuEventHandler::left() const
{
	
}

void MenuEventHandler::right() const
{

}

