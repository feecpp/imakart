#include "MenuLogic.hpp"
#include <iostream>

MenuLogic::MenuLogic():
	nbButtonInMenu(0), positionButtonSelected(0){
}

const InterfaceElement* MenuLogic::getTabInterfaceElement(const unsigned int positionOfElement){
	if(positionOfElement < nbButtonInMenu)
		return tabButtonLogicMenu[positionOfElement];
	else
		return NULL;
}

MenuLogic* MenuLogic::initialiseMainMenu(){
	MenuLogic* mainMenu = new MenuLogic;
	
	ButtonLogic* jouer = new ButtonLogic("jouer");
	ButtonLogic* options = new ButtonLogic("options");
	ButtonLogic* credits = new ButtonLogic("credits");
	ButtonLogic* quitter = new ButtonLogic("quitter");
	
	mainMenu->addButton(jouer);
	mainMenu->addButton(options);
	mainMenu->addButton(credits);
	mainMenu->addButton(quitter);
	
	return mainMenu;
}

void MenuLogic::addButton(ButtonLogic* buttonToAdd){
	tabButtonLogicMenu.push_back(buttonToAdd);
	if(nbButtonInMenu == 0){
		tabButtonLogicMenu[0]->changeState();
	}
	++nbButtonInMenu;
}

void MenuLogic::nextButton(){
	tabButtonLogicMenu[positionButtonSelected]->changeState();
	++positionButtonSelected;
	if(positionButtonSelected >= nbButtonInMenu) {
		positionButtonSelected = 0;
	}
	tabButtonLogicMenu[positionButtonSelected]->changeState();
}

void MenuLogic::previousButton(){
	tabButtonLogicMenu[positionButtonSelected]->changeState();
	if(positionButtonSelected == 0) {
		positionButtonSelected = nbButtonInMenu-1;
	} else {
		--positionButtonSelected;
	}
	tabButtonLogicMenu[positionButtonSelected]->changeState();
}

void MenuLogic::submitButton(){
	tabButtonLogicMenu[positionButtonSelected]->submit();
}

MenuLogic::~MenuLogic(){
}
