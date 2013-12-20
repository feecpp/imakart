#ifndef BUTTONLOGIC_HPP
#define BUTTONLOGIC_HPP

#include "InterfaceElement.hpp"
#include "ButtonActionEnum.hpp"
#include <string>

class ButtonLogic : public InterfaceElement
{
public:
	std::string name; // name of the button
	
	ButtonLogic(const std::string name); // Create a logical button with no graphic representation
	~ButtonLogic();

	void changeState();
	void setAction(ButtonAction theAction);
	ButtonAction getButtonAction(); //what the button do when you press enter
	const bool isSelected() const;

private:
	bool selected; // -1 unselect / 1 select 
	ButtonAction actionToDo;
};

#endif // BUTTONLOGIC_HPP
