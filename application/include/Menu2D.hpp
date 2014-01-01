#ifndef MENU2D_HPP
#define MENU2D_HPP

#include <string>
#include <vector>
#include "Button2D.hpp"

class Menu2D: public Object2D
{
public:
	unsigned int nbButtonInMenu;

	Menu2D();
	~Menu2D();
	
	Button2D* getTab2DMenu(const unsigned int positionToSelect)
		{return tab2DMenu[positionToSelect];}
	
	static Menu2D* initialiseMainMenu();
	static Menu2D* initialiseOptionsMenu();
	static Menu2D* initialiseKartMenu(std::vector <std::string> kartsName);
	static Menu2D* initialiseMapMenu();

	void addButton(Button2D* buttonToAdd);
    void update();
	void draw(const glimac::ShaderProgram& shaderProgram) const;
	
private:
	std::vector<Button2D* > tab2DMenu;
	InterfaceElement* model;
};

#endif //MENU2D_HPP
