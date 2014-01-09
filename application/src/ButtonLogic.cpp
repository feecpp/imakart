#include "ButtonLogic.hpp"

ButtonLogic::ButtonLogic(const std::string name):
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
