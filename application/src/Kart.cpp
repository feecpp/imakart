#include "Kart.hpp"
#include <iostream>
<<<<<<< HEAD

Kart::Kart():
			position(), speed(0.f), glimac::Vertex2D(0.f,0.f){
				
}
Kart::Kart(Point3D pos_, float speed_, glimac::Vertex2D dir_):
			position(pos_), speed(speed_) direction(dir_){
	
}

// The Kart goes forward : its position changes
void Kart::moveForward(){
	std::cout << "J'avance" << std::endl;
	position.y ++; //J'ai changé y mais ce ne sera pas forcément ça au final 
}

//The Kart goes back : its position changes
void Kart::moveBackward(){
	std::cout << "Je recule" << std::endl;
	position.y --;
}

// The Kart goes left : its direction changes
void Kart::turnLeft(){
	std::cout << "Je tourne à droite" << std::endl;
	direction.x ++;
}

// The Kart goes left : its direction changes
void Kart::turnRight(){
	std::cout << "Je tourne à gauche" << std::endl;
	direction.x --;
}
