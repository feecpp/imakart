#include "Menu.hpp"
#include <iostream>

Menu::Menu(const unsigned int nb_button_in_menu):
	nb_button_in_menu(nb_button_in_menu), position_to_add(0) {
		
	tab_button_menu = (ButtonLogic*)malloc(sizeof(ButtonLogic) * nb_button_in_menu);
	if(tab_button_menu == NULL) {
		std::cerr << "Enable to alloc Tab Button Menu" << std::endl;
	}
}

void Menu::add_button(const ButtonLogic& button_to_add){
	if(position_to_add < nb_button_in_menu) {
		tab_button_menu[position_to_add] = button_to_add;
		if(position_to_add == 0){
			tab_button_menu[0].changeState();
			position_button_selected = 0;
		}
		++position_to_add;
	} else {
		++nb_button_in_menu;
		tab_button_menu = (ButtonLogic*)realloc(tab_button_menu, sizeof(ButtonLogic) * nb_button_in_menu);
		if(tab_button_menu == NULL) {
			std::cerr << "Enable to realloc Tab Button Menu" << std::endl;
		}
		tab_button_menu[position_to_add] = button_to_add;
		++position_to_add;
	}
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
		if(i < position_to_add) {
			tab_button_menu[i].getGraphicRepresentation()->draw();
		} else {
			return;
		}
	}
}

Menu::~Menu(){
	free(tab_button_menu);
}
