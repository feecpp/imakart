#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Vertex2DRGB.hpp"
#include <glm/glm.hpp>

class Button2D{
public:
	Button2D(); // Unit square
	Button2D(const float x_bottom, const float y_left, const float width, const float height);
	
	const GLfloat* getVertices() const;

private:
	GLfloat vertices[8];
};

#endif // BUTTON_HPP
