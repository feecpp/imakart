#ifndef MENU2D_HPP
#define MENU2D_HPP

#include <vector>
#include "Button2D.hpp"

class MenuEventHandler;

class Menu2D: public Object2D
{
public:
	unsigned int nbButtonInMenu;

	Menu2D();
	~Menu2D();
	
	void initialiseMainMenu();
	void addButton(Button2D* buttonToAdd);
    
	void draw();
	
private:
	std::vector<Button2D* > tab2DMenu;
	InterfaceElement* model;
};

#endif //MENU2D_HPP
