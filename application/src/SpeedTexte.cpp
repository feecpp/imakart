#include "SpeedTexte.hpp"
#include <iostream>

SpeedTexte::SpeedTexte(const float* pSpeedKart):
	Texte2D::Texte2D(glimac::convert(*pSpeedKart)), pCurrentSpeedKart(pSpeedKart)
	{}

SpeedTexte::~SpeedTexte(){}

void SpeedTexte::update(){
	myText = glimac::convert(*pCurrentSpeedKart);
	setPosition(350, 570, 20);

}