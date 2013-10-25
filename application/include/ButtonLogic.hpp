#ifndef BUTTONLOGIC_HPP
#define BUTTONLOGIC_HPP

class ButtonLogic{
public:
	const char* name;
	int state; // -1 unselect / 1 select 
	
	ButtonLogic(const char* name);
	
	changeState();
};

#endif // BUTTONLOGIC_HPP
