#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include "ButtonLogic.hpp" 

class MenuEventHandler;

class Menu{
public:
	unsigned int nb_button_in_menu;
	
	Menu();
	~Menu();
	
	void create_main_menu();
	
	void add_button(const ButtonLogic& button_to_add);
	void next_button();
	void previous_button();
	
	void draw();
	
private:
	std::vector<ButtonLogic> tab_button_menu;
	unsigned int position_button_selected;
};

#endif //MENU_HPP
