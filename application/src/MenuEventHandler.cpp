#include "MenuEventHandler.hpp"
#include "GameEngine.hpp"
#include "ButtonActionEnum.hpp"
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
	ButtonAction action = gameEngine.getMenuLogic().submitButton();
	ButtonLogic* button = gameEngine.getMenuLogic().getButtonLogicSelected();

	switch(action){
		case PLAY:
			std::cout << "Play pressed" << std::endl;
			gameEngine.setState(IN_MENU_KART);
			break;

		case OPTIONS:
			break;

		case CREDITS:
			break;

		case EXIT:
     		gameEngine.activateExitFlag();
			break;

		case SELECT:
      		gameEngine.setupPlayer(button->name);

			std::cout << "Kart player game engine : " << gameEngine.getPlayer().getKart().getName() << std::endl;

			gameEngine.setState(IN_RACE);
			break;

		default:
			std::cout << "No implementation" << std::endl;
			break;
	}

}
void MenuEventHandler::releaseEnter() const
{

}

void MenuEventHandler::pressSpace() const {}
void MenuEventHandler::releaseSpace() const {}

