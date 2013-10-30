#ifndef MENULOGIC_HPP
#define MENULOGIC_HPP

#include <vector>
#include "ButtonLogic.hpp" 

class MenuEventHandler;

class MenuLogic
{
public:
	unsigned int nbButtonInMenu;

	MenuLogic();
	~MenuLogic();
	
	const InterfaceElement* getButtonLogicFromTabButtonLogicMenu(const unsigned int positionOfButton);
	
	void initialiseMainMenu();
	void addButton(ButtonLogic* buttonToAdd);
	void nextButton();
	void previousButton();
	
private:
	unsigned int positionButtonSelected;
	std::vector<ButtonLogic* > tabButtonLogicMenu;
};

#endif //MENULOGIC_HPP

