#include "MenuEventHandler.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"
#include "ButtonActionEnum.hpp"
#include <iostream>
#include <cstring>

MenuEventHandler::MenuEventHandler(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine)
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
  gameEngine.getMenuLogic().previousButton();
}
void MenuEventHandler::releaseLeft() const
{
}

void MenuEventHandler::pressRight() const
{
  gameEngine.getMenuLogic().nextButton();
}
void MenuEventHandler::releaseRight() const
{

}

void MenuEventHandler::pressEnter() const
{
	ButtonAction action = gameEngine.getMenuLogic().submitButton();
	ButtonLogic* button = gameEngine.getMenuLogic().getButtonLogicSelected();

	std::string str = button->name;
	char * cstr = new char [str.length()+1];
	std::strcpy (cstr, str.c_str());
	char * p = std::strtok (cstr,"*");

	int width;
	int height;

	switch(action){
		case PLAY:
			gameEngine.setState(IN_MENU_KART);
			break;

		case OPTIONS:
			gameEngine.setState(IN_MENU_OPTIONS);
			break;
			
		case EXIT:
     		gameEngine.activateExitFlag();
			break;

		case SELECT:
      		gameEngine.setupPlayer(button->name);

			gameEngine.setState(IN_RACE);
			break;

		case WINDOW_RESIZE:
			width = atoi(p);
	        p = strtok(NULL," ");
	        height = atoi(p);


	        graphicEngine.getWorld3D()->setSize(width, height);
	        graphicEngine.getWindow().setSize(sf::Vector2u(width, height));

	        graphicEngine.setNewSizeWindow(width, height);
	        graphicEngine.init();
	        gameEngine.setState(IN_MENU);
	        
			break;

		case RETURN_MAIN_MENU:
			gameEngine.setState(IN_MENU);
			break;

		default:
			std::cout << "No implementation" << std::endl;
			break;
	}

    delete[] cstr;
}

void MenuEventHandler::releaseEnter() const
{

}

void MenuEventHandler::pressSpace() const {}
void MenuEventHandler::releaseSpace() const {}
void MenuEventHandler::pressNumpad0() const {}
void MenuEventHandler::releaseNumpad0() const {}
