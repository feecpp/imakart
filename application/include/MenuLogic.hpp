#ifndef MENULOGIC_HPP
#define MENULOGIC_HPP

#include <string>
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
	
	const InterfaceElement* getTabInterfaceElement(const unsigned int positionOfElement);
	const bool isSelected() const
		{return false;}
		
	static MenuLogic* initialiseMainMenu();
	static MenuLogic* initialiseKartMenu(std::vector <std::string> kartsName);
	static MenuLogic* initialiseMapMenu();

	void addButton(ButtonLogic* buttonToAdd);
	void nextButton();
	void previousButton();
	ButtonAction submitButton();

	ButtonLogic* getButtonLogicSelected()
		{return tabButtonLogicMenu[positionButtonSelected];}
	
private:
	unsigned int positionButtonSelected;
	std::vector<ButtonLogic* > tabButtonLogicMenu;
};

#endif //MENULOGIC_HPP

