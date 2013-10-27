#ifndef MENU_HPP
#define MENU_HPP

#include "ButtonLogic.hpp" 

class MenuEventHandler;

class Menu{
public:
	unsigned int nb_button_in_menu;
	
	Menu(const unsigned int nb_button_in_menu = 1);
	~Menu();
	
	void add_button(const ButtonLogic& button_to_add);
	void next_button();
	void previous_button();
	
	void draw();
	
private:
	MenuEventHandler* handle;
	ButtonLogic* tab_button_menu;
	unsigned int position_to_add;
	unsigned int position_button_selected;
};

#endif //MENU_HPP
