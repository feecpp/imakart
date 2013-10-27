#ifndef BUTTONLOGIC_HPP
#define BUTTONLOGIC_HPP

#include "Button2D.hpp"

class ButtonLogic{
public:
	const char* name; // name of the button
	
	ButtonLogic(const char* name); // Create a logical button with no graphic representation
	ButtonLogic(const char* name, Button2D* graphic_button); // Create a logical button with a link to a Button2D
	ButtonLogic(const char* name, const float x_bottom, const float y_left, const float width, const float height); // Create a logical button with a graphic button
	~ButtonLogic();
	
	Button2D* getGraphicRepresentation() const;
	
	void changeState();

private:
	int stateButton; // -1 unselect / 1 select 
	Button2D* graphic_representation;
};

#endif // BUTTONLOGIC_HPP
