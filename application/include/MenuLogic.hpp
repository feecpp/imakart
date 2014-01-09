#ifndef MENULOGIC_HPP
#define MENULOGIC_HPP

#include <vector>
#include "ButtonActionEnum.hpp"
#include "ButtonLogic.hpp"

class MenuLogic : public InterfaceElement
{
public:
  unsigned int nbButtonInMenu;

  MenuLogic();
  ~MenuLogic();
  
  MenuLogic& operator=(MenuLogic& other);
  
  const InterfaceElement* getTabInterfaceElement(const unsigned int positionOfElement);
  const bool isSelected() const
    {return false;}
    
  static MenuLogic* initialiseMainMenu();
  static MenuLogic* initialiseOptionsMenu();
  static MenuLogic* initialiseKartMenu(std::vector <std::string> kartsName);
  static MenuLogic* initialiseMapMenu(std::vector <std::string> mapsName);
  static MenuLogic* initialiseRaceMenu();

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

