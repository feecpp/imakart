#include "Menu.hpp"
#include <iostream>

Menu::Menu():
	nb_button_in_menu(0), position_button_selected(0){}

void Menu::create_main_menu(){
	ButtonLogic jouer("jouer", -0.3, 0.3, 0.6, 0.2);
	add_button(jouer);
	ButtonLogic options("options", -0.3, 0.0, 0.6, 0.2);
	add_button(options);
	ButtonLogic credits("credits", -0.3, -0.3, 0.6, 0.2);
	add_button(credits);
	ButtonLogic quitter("quitter", -0.3, -0.6, 0.6, 0.2);
	add_button(quitter);
}

void Menu::add_button(const ButtonLogic& button_to_add){
		tab_button_menu.push_back(button_to_add);
		if(nb_button_in_menu == 0){
			tab_button_menu[0].changeState();
		}
		++nb_button_in_menu;
}

void Menu::next_button(){
	tab_button_menu[position_button_selected].changeState();
	++position_button_selected;
	if(position_button_selected >= nb_button_in_menu) {
		position_button_selected = 0;
	}
	tab_button_menu[position_button_selected].changeState();
}

void Menu::previous_button(){
	tab_button_menu[position_button_selected].changeState();
	if(position_button_selected == 0) {
		position_button_selected = nb_button_in_menu-1;
	} else {
		--position_button_selected;
	}
	tab_button_menu[position_button_selected].changeState();
}

void Menu::draw(){
	for(unsigned int i = 0; i < nb_button_in_menu; ++i){
		tab_button_menu[i].getGraphicRepresentation()->draw();
	}
}

Menu::~Menu(){
}
