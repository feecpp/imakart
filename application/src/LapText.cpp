#include "LapText.hpp"
#include <iostream>

LapText::LapText(const unsigned int& currentLap):
	Texte2D::Texte2D(glimac::convertToIntString(currentLap)), currentLap(currentLap)
	{}

LapText::~LapText(){}

void LapText::update(){
	myText = "Tour ";
	myText = myText + glimac::convertToIntString(currentLap);
  myText = myText + "/2";
	setPosition(10, 540, 20);

}
