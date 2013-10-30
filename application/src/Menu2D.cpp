#include "Menu2D.hpp"
#include "MenuLogic.hpp"
#include <iostream>

Menu2D::Menu2D():
	nbButtonInMenu(0){}

void Menu2D::initialiseMainMenu(){
	Button2D* jouer = new Button2D(-0.3, 0.3, 0.6, 0.2);
	Button2D* options = new Button2D(-0.3, 0.0, 0.6, 0.2);
	Button2D* credits = new Button2D(-0.3, -0.3, 0.6, 0.2);
	Button2D* quitter = new Button2D(-0.3, -0.6, 0.6, 0.2);
	
	MenuLogic* mainMenuLogic = new MenuLogic();
	mainMenuLogic->initialiseMainMenu();

	jouer->setModelToRepresent( *(mainMenuLogic->getButtonLogicFromTabButtonLogicMenu(0)) );
	options->setModelToRepresent( *(mainMenuLogic->getButtonLogicFromTabButtonLogicMenu(1)) );
	credits->setModelToRepresent( *(mainMenuLogic->getButtonLogicFromTabButtonLogicMenu(2)) );
	quitter->setModelToRepresent( *(mainMenuLogic->getButtonLogicFromTabButtonLogicMenu(3)) );

	addButton(jouer);
	addButton(options);
	addButton(credits);
	addButton(quitter);
}

void Menu2D::addButton(Button2D* buttonToAdd){
		tab2DMenu.push_back(buttonToAdd);
		if(nbButtonInMenu == 0){
			tab2DMenu[0]->updateState();
		}
		++nbButtonInMenu;
}

void Menu2D::draw(){

	for(unsigned int i = 0; i < nbButtonInMenu; ++i){
		tab2DMenu[i]->draw();
	}
}

Menu2D::~Menu2D(){
}
