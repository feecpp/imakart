#include "ButtonLogic.hpp"
#include <iostream>

ButtonLogic::ButtonLogic(const char* name):
	name(name), stateButton(-1) {};

ButtonLogic::ButtonLogic(const char* name, Button2D* graphic_button):
	name(name), stateButton(-1), graphic_representation(graphic_button) {};

ButtonLogic::ButtonLogic(const char* name, const float x_bottom, const float y_left, const float width, const float height):
	name(name), stateButton(-1) {
	graphic_representation = new Button2D(x_bottom, y_left, width, height);
}

ButtonLogic::~ButtonLogic(){
}
	
Button2D* ButtonLogic::getGraphicRepresentation() const{
	return graphic_representation;
}

void ButtonLogic::changeState(){
	stateButton = -stateButton;
	graphic_representation->updateState(stateButton);
}
