#ifndef MENU_HPP
#define MENU_HPP

#include "ButtonLogic.hpp" 

class Menu{
public:
	unsigned int nb_button_in_menu;
	
	Menu(const unsigned int nb_button_in_menu = 1);
	~Menu();
	
	void add_button(const ButtonLogic& button_to_add);
	
	void draw();
	
private:
	ButtonLogic* tab_button_menu;
	unsigned int position_to_add;
};

#endif //MENU_HPP
