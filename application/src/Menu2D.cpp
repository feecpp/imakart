#include "Menu2D.hpp"

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

Menu2D* Menu2D::initialiseKartMenu(std::vector <std::string> kartsName){
	Menu2D* kartMenu = new Menu2D;
	for(unsigned int i = 0; i < kartsName.size(); ++i){
		std::string textures = "textures/karts/";
		textures = textures + kartsName[i];
		std::string texturesS = textures + "Selected.jpg";
		textures = textures + ".jpg";
		Button2D* kart = new Button2D(- 0.9 + i * 0.6, -0.25, 0.5, 0.5, textures, texturesS, kartsName[i]);
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
