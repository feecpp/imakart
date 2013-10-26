#pragma once

struct Point3D{
	float x;
	float y;
	float z;
	
	Point3D();
	Point3D(float x_, float y_, float z_);
	Point3D(Point3D& other);
};
