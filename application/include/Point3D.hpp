#pragma once

struct Point3D{
	float x;
	float y;
	
	Point3D();
	Point3D(float x_, float y_);
	Point3D(Point3D& other);
};
