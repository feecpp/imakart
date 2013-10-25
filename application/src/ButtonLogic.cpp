#include "ButtonLogic.hpp"

ButtonLogic::ButtonLogic(const char* name):
	name(name), state(-1) {};

ButtonLogic::changeState(){
	state = -state;
}
