#pragma once

#include "Point3D.hpp"
#include "Vertex2DRGB.hpp"

class Kart{
	private:
		Point3D position;
		float speed;
		glimac::Vertex2D direction;
	
	public:
		Kart();
		Kart(Point3D pos_, float speed_, glimac::Vertex2D dir_);
		
		void moveForward();
		void moveBackward();
		void turnLeft();
		void turnRight();
};
