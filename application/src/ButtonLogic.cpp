#include "ButtonLogic.hpp"
#include <iostream>

ButtonLogic::ButtonLogic(const char* name):
	selected(false){
		this->name = name;
	};

ButtonLogic::~ButtonLogic(){
	
}

void ButtonLogic::setAction(ButtonAction theAction){
	actionToDo = theAction;
}

void ButtonLogic::changeState(){
	selected = !selected;
}

ButtonAction ButtonLogic::getButtonAction(){
	return actionToDo;
}

const bool ButtonLogic::isSelected() const{
	return selected;
}
