#include "MenuLogic.hpp"

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
	ButtonLogic* quitter = new ButtonLogic("quitter");

	jouer->setAction(PLAY);
	options->setAction(OPTIONS);
	quitter->setAction(EXIT);

	mainMenu->addButton(jouer);
	mainMenu->addButton(options);
	mainMenu->addButton(quitter);
	
	return mainMenu;
}

MenuLogic* MenuLogic::initialiseOptionsMenu(){
	MenuLogic* optionMenu = new MenuLogic;
	
	ButtonLogic* sizeWindow1 = new ButtonLogic("800*600");
	ButtonLogic* sizeWindow2 = new ButtonLogic("1024*768");
	ButtonLogic* sizeWindow3 = new ButtonLogic("1600*1200");

	ButtonLogic* returnMainMenu = new ButtonLogic("returnMainMenu");

	sizeWindow1->setAction(WINDOW_RESIZE);
	sizeWindow2->setAction(WINDOW_RESIZE);
	sizeWindow3->setAction(WINDOW_RESIZE);

	returnMainMenu->setAction(RETURN_MAIN_MENU);

	optionMenu->addButton(sizeWindow1);
	optionMenu->addButton(sizeWindow2);
	optionMenu->addButton(sizeWindow3);
	optionMenu->addButton(returnMainMenu);
	
	return optionMenu;
}

MenuLogic* MenuLogic::initialiseKartMenu(std::vector <std::string> kartsName){
	MenuLogic* kartMenu = new MenuLogic;

	for(unsigned int i = 0; i < kartsName.size(); ++i){
		ButtonLogic* kart = new ButtonLogic(kartsName[i]);
		kart->setAction(SELECT);
		kartMenu->addButton(kart);
	}

	ButtonLogic* returnMainMenu = new ButtonLogic("returnMainMenu");
	returnMainMenu->setAction(RETURN_MAIN_MENU);
	kartMenu->addButton(returnMainMenu);

	return kartMenu;
}

MenuLogic* MenuLogic::initialiseMapMenu(){
	MenuLogic* mapMenu = new MenuLogic;
	return mapMenu;
}

MenuLogic* MenuLogic::initialiseRaceMenu(){
	MenuLogic* raceMenu = new MenuLogic;

	ButtonLogic* reprendre = new ButtonLogic("reprendre");
	ButtonLogic* quitter = new ButtonLogic("quitter");

	reprendre->setAction(TAKE_BACK);
	quitter->setAction(EXIT);

	raceMenu->addButton(reprendre);
	raceMenu->addButton(quitter);
	
	return raceMenu;
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

ButtonAction MenuLogic::submitButton(){
	return tabButtonLogicMenu[positionButtonSelected]->getButtonAction();
}

MenuLogic::~MenuLogic(){
	for (size_t i = 0; i < tabButtonLogicMenu.size(); ++i)
	{
	  delete tabButtonLogicMenu[i];
	}
}
