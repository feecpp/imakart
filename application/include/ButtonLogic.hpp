#ifndef BUTTONLOGIC_HPP
#define BUTTONLOGIC_HPP

#include "Button2D.hpp"
#include "InterfaceElement.hpp"

class ButtonLogic : public InterfaceElement
{
public:
	//const char* name; // name of the button
	
	ButtonLogic(const char* name); // Create a logical button with no graphic representation
	~ButtonLogic();

	void changeState();
	const bool isSelected() const;

private:
	bool selected; // -1 unselect / 1 select 
};

#endif // BUTTONLOGIC_HPP
