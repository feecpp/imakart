#ifndef KART_HPP
#define KART_HPP

#include "Point3D.hpp"
#include "Vertex2DRGB.hpp"

class Kart{
	private:
		glm::vec3 position;
		float speed;
		glimac::Vertex2D direction;
	
	public:
		Kart();
		Kart(glm::vec3 pos_, float speed_, glimac::Vertex2D dir_);
		
		void moveForward();
		void moveBackward();
		void turnLeft();
		void turnRight();
};

#endif