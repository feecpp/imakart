#include "Button.hpp"

Button2D::Button2D(){
	vertices[0] = -0.5f;
	vertices[1] = -0.5f;
	vertices[2] = 0.5f;
	vertices[3] = -0.5f;
	vertices[4] = 0.5f;
	vertices[5] = 0.5f;
	vertices[6] = -0.5f;
	vertices[7] = 0.5f;
}

Button2D::Button2D(const float x_bottom, const float y_left, const float width, const float height){
	vertices[0] = x_bottom;
	vertices[1] = y_left;
	vertices[2] = x_bottom + width;
	vertices[3] = y_left;
	vertices[4] = x_bottom + width;
	vertices[5] = y_left + height;
	vertices[6] = x_bottom;
	vertices[7] = y_left + height;
}

const GLfloat* Button2D::getVertices() const{
	return vertices;
}
