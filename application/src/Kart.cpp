#include "Kart.hpp"

Kart::Kart():
			position(), speed(0.f), glimac::Vertex2D(0.f,0.f){
				
}
Kart::Kart(Point3D pos_, float speed_, glimac::Vertex2D dir_):
			position(pos_), speed(speed_) direction(dir_){
	
}

// The Kart goes forward : its position changes
void Kart::moveForward(){
	position.y ++; //J'ai changé y mais ce ne sera pas forcément ça au final 
}

//The Kart goes back : its position changes
void Kart::moveBackward(){
	position.y --;
}

// The Kart goes left : its direction changes
void Kart::turnLeft(){
	direction.x ++;
}

// The Kart goes left : its direction changes
void Kart::turnRight(){
	direction.x --;
}