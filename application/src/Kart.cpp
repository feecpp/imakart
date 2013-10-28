#include "Kart.hpp"
#include <iostream>

Kart::Kart()
  : position(0.f, 0.f, 0.f), direction(0.f, 0.f, 0.f), speed(0.f)
{
}

Kart::Kart(glm::vec3 position, glm::vec3 direction, float speed)
  : position(position), direction(direction), speed(speed)
{
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

const glm::vec3& Kart::getPosition() const
  {return position;}
const glm::vec3& Kart::getOrientation() const
  {return direction;}
