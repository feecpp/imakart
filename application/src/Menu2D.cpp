#include "Menu2D.hpp"
#include "MenuLogic.hpp"
#include <iostream>

Menu2D::Menu2D():
	nbButtonInMenu(0){}

Menu2D* Menu2D::initialiseMainMenu(){
	
	Menu2D* mainMenu = new Menu2D;
	
	Button2D* jouer = new Button2D(-0.3, 0.3, 0.6, 0.2);
	Button2D* options = new Button2D(-0.3, 0.0, 0.6, 0.2);
	Button2D* credits = new Button2D(-0.3, -0.3, 0.6, 0.2);
	Button2D* quitter = new Button2D(-0.3, -0.6, 0.6, 0.2);

	mainMenu->addButton(jouer);
	mainMenu->addButton(options);
	mainMenu->addButton(credits);
	mainMenu->addButton(quitter);
	
	return mainMenu;
}

void Menu2D::addButton(Button2D* buttonToAdd){
		tab2DMenu.push_back(buttonToAdd);
		++nbButtonInMenu;
}

void Menu2D::update(){
	for(unsigned int i = 0; i < nbButtonInMenu; ++i){
		tab2DMenu[i]->update();
	}
}

void Menu2D::draw(const glimac::ShaderProgram& shaderProgram) const{
	for(unsigned int i = 0; i < nbButtonInMenu; ++i){
		tab2DMenu[i]->draw(shaderProgram);
	}
}

Menu2D::~Menu2D(){
	for (size_t i = 0; i < tab2DMenu.size(); ++i)
	{
	  delete tab2DMenu[i];
	}
	tab2DMenu.clear();
}
