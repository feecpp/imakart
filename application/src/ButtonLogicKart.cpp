#include "ButtonLogicKart.hpp"
#include "Hangar.hpp"

ButtonLogicKart::ButtonLogicKart(const std::string name):
  ButtonLogic::ButtonLogic(name), kart(Hangar::getSingletonHangar()->getKartByName(name)){
};

ButtonLogicKart::~ButtonLogicKart(){
  
}
