#pragma once

class Kart{
	Point3D position;
	float speed;
	Vect3D direction;
	
	
	Kart();
	Kart(Point3D pos_, float speed_, Vect3D dir_);
	
	moveForward();
	moveBackWard();
	turnLeft();
	turnRight();
};
