#ifndef BUTTONLOGICKART_HPP
#define BUTTONLOGICKART_HPP

#include "ButtonLogic.hpp"
#include "Kart.hpp"
#include <string>

class ButtonLogicKart : public ButtonLogic
{
public:  
  ButtonLogicKart(const std::string name); // Create a logical button with no graphic representation
  ~ButtonLogicKart();

private:;
  Kart& kart;
};

#endif // BUTTONLOGIC_HPP
