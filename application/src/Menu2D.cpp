#include "Menu2D.hpp"
#include "Button2DKart.hpp"
#include "Hangar.hpp"
#include "Kart.hpp"
#include "convert.hpp"

Menu2D::Menu2D():
	nbButtonInMenu(0){}

Menu2D* Menu2D::initialiseMainMenu(){
	
	Menu2D* mainMenu = new Menu2D;
	
	Button2D* jouer = new Button2D(-0.3, 0.3, 0.6, 0.2, "textures/jouer.png", "textures/jouerSelect.png", "jouer");
	Button2D* options = new Button2D(-0.3, 0.0, 0.6, 0.2, "textures/options.png", "textures/optionsSelect.png", "options");
	Button2D* credits = new Button2D(-0.3, -0.3, 0.6, 0.2, "textures/credits.png", "textures/creditsSelect.png", "credits");
	Button2D* quitter = new Button2D(-0.3, -0.6, 0.6, 0.2, "textures/quitter.png", "textures/quitterSelect.png", "quitter");

	mainMenu->addButton(jouer);
	mainMenu->addButton(options);
	mainMenu->addButton(credits);
	mainMenu->addButton(quitter);
	
	return mainMenu;
}

Menu2D* Menu2D::initialiseOptionsMenu(){
	
	Menu2D* optionsMenu = new Menu2D;
	
	Button2D* sizeWindow1 = new Button2D(-0.8, 0.1, 0.5, 0.5, "textures/options/windowSize1.png", "textures/options/windowSize1Select.png", "800*600");
	Button2D* sizeWindow2 = new Button2D(-0.25, 0.1, 0.5, 0.5, "textures/options/windowSize2.png", "textures/options/windowSize2Select.png", "1024*768");
	Button2D* sizeWindow3 = new Button2D(0.3, 0.1, 0.5, 0.5, "textures/options/windowSize3.png", "textures/options/windowSize3Select.png", "1600*1200");

	Button2D* returnMainMenu = new Button2D(-0.3, -0.3, 0.6, 0.2, "textures/options/returnMainMenu.png", "textures/options/returnMainMenuSelect.png", "returnMainMenu");

	optionsMenu->addButton(sizeWindow1);
	optionsMenu->addButton(sizeWindow2);
	optionsMenu->addButton(sizeWindow3);

	optionsMenu->addButton(returnMainMenu);
	
	return optionsMenu;
}


Menu2D* Menu2D::initialiseKartMenu(std::vector <std::string> kartsName){
	Menu2D* kartMenu = new Menu2D;
	for(unsigned int i = 0; i < kartsName.size(); ++i){
		std::string textures = "textures/karts/";
		textures = textures + kartsName[i];
		std::string texturesS = textures + "Selected.jpg";
		textures = textures + ".jpg";
		Specifications spe = Hangar::getSingletonHangar()->getKartByName(kartsName[i]).specifications;
		std::vector<std::string> caracteristique;
		caracteristique.push_back(glimac::convert(spe.acceleration));
		caracteristique.push_back(glimac::convert(spe.maxSpeed));
		caracteristique.push_back(glimac::convert(spe.weight));
    Button2DKart* kart = new Button2DKart(- 0.9 + i * 0.6, -0.25, 0.5, 0.5, textures, texturesS, kartsName[i], caracteristique, i);
		kartMenu->addButton(kart);
	}

	return kartMenu;
}

Menu2D* Menu2D::initialiseMapMenu(){
	Menu2D* mapMenu = new Menu2D;

	return mapMenu;
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
