#include "MenuLogic.hpp"
#include <iostream>

MenuLogic::MenuLogic():
	nbButtonInMenu(0), positionButtonSelected(0){
}

ButtonLogic MenuLogic::getButtonLogicFromTabButtonLogicMenu(const unsigned int positionOfButton){
	if(positionOfButton < nbButtonInMenu)
		return *(tabButtonLogicMenu[positionOfButton]);
	else
		return NULL;
}

void MenuLogic::initialiseMainMenu(){
	ButtonLogic* jouer = new ButtonLogic("jouer");
	ButtonLogic* options = new ButtonLogic("options");
	ButtonLogic* credits = new ButtonLogic("credits");
	ButtonLogic* quitter = new ButtonLogic("quitter");
	addButton(jouer);
	addButton(options);
	addButton(credits);
	addButton(quitter);
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

MenuLogic::~MenuLogic(){
}
