#include "ButtonLogic.hpp"
#include <iostream>

ButtonLogic::ButtonLogic(const char* name):
	name(name), selected(false) {};

ButtonLogic::~ButtonLogic(){
}

void ButtonLogic::changeState(){
	selected = !selected;
}

const bool ButtonLogic::isSelected() const{
	return selected;
}
