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
	std::cout << "J'avance" << std::endl;
	direction.y = 1.0;
	position += direction; 
}

//The Kart goes back : its position changes
void Kart::moveBackward(){
	std::cout << "Je recule" << std::endl;
	direction.y = -1.0;
	position += direction;
}

// The Kart goes left : its direction changes
void Kart::turnLeft(){
	std::cout << "Je tourne à gauche" << std::endl;
	direction.x = -1.0;
	position += direction;
}

// The Kart goes left : its direction changes
void Kart::turnRight(){
	std::cout << "Je tourne à droite" << std::endl;
	direction.x = 1.0;
	position += direction;
}

const glm::vec3& Kart::getPosition() const
  {return position;}
const glm::vec3& Kart::getOrientation() const
  {return direction;}
