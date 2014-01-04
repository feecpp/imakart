#include "SpeedTexte.hpp"
#include <iostream>

SpeedTexte::SpeedTexte(const float* pSpeedKart):
	Texte2D::Texte2D(glimac::convertToIntString(*pSpeedKart)), pCurrentSpeedKart(pSpeedKart)
	{}

SpeedTexte::~SpeedTexte(){}

void SpeedTexte::update(){
	myText = glimac::convertToIntString(*pCurrentSpeedKart);
	myText = myText + " lumatas";
	setPosition(350, 570, 20);

}