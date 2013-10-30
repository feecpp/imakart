#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "InterfaceElement.hpp"
#include "Object2D.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Vertex2DRGB.hpp"


class Button2D : public Object2D
{
public:
	Button2D(); // Unit square
	Button2D(const float x_bottom, const float y_left, const float width, const float height); 
	~Button2D();
	
	const glimac::Vertex2DRGB* getVertices() const;
	void updateVertices(const float x_bottom, const float y_left, const float width, const float height);

	void draw();
	void updateState();
	
private:
	glimac::Vertex2DRGB vertices[4];
	glimac::LowLevelVBO vbo;
	glimac::VAO vao;
	
	bool done;
	void setVBO(); //call in the constructor
	void setVAO(); //call in the constructor
};

#endif // BUTTON_HPP
