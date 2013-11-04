#include "ButtonLogic.hpp"
#include <iostream>

ButtonLogic::ButtonLogic(const char* name):
	selected(false) {
		this->name = name;
	};

ButtonLogic::~ButtonLogic(){
}

void ButtonLogic::changeState(){
	selected = !selected;
}

void ButtonLogic::submit(){
	
}

const bool ButtonLogic::isSelected() const{
	return selected;
}
