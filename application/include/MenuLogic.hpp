#ifndef MENULOGIC_HPP
#define MENULOGIC_HPP

#include <vector>
#include "ButtonLogic.hpp" 

class MenuEventHandler;
class InterfaceElement;

class MenuLogic : public InterfaceElement
{
public:
	unsigned int nbButtonInMenu;

	MenuLogic();
	~MenuLogic();
	
	const InterfaceElement* getButtonLogicFromTabButtonLogicMenu(const unsigned int positionOfButton);
	const bool isSelected() const
		{return false;}

	void initialiseMainMenu();
	void addButton(ButtonLogic* buttonToAdd);
	void nextButton();
	void previousButton();
	
private:
	unsigned int positionButtonSelected;
	std::vector<ButtonLogic* > tabButtonLogicMenu;
};

#endif //MENULOGIC_HPP

