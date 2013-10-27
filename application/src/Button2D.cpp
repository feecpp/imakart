#include "Button2D.hpp"
#include <iostream>

Button2D::Button2D(){
	vertices[0] = glimac::Vertex2DRGB(glm::vec2(-0.5f, -0.5f), glm::vec3(0.f,1.f,0.f));
	vertices[1] = glimac::Vertex2DRGB(glm::vec2(0.5f, -0.5f), glm::vec3(0.f,1.f,1.f));
	vertices[2] = glimac::Vertex2DRGB(glm::vec2(0.5f, 0.5f), glm::vec3(1.f,1.f,0.f));
	vertices[3] = glimac::Vertex2DRGB(glm::vec2(-0.5f, 0.5f), glm::vec3(0.f,0.f,1.f));
	
	setVBO();
	setVAO();
}

Button2D::Button2D(const float x_bottom, const float y_left, const float width, const float height){
	vertices[0] = glimac::Vertex2DRGB(glm::vec2(x_bottom, y_left), glm::vec3(0.f,1.f,0.f));
	vertices[1] = glimac::Vertex2DRGB(glm::vec2(x_bottom + width, y_left), glm::vec3(0.f,1.f,1.f));
	vertices[2] = glimac::Vertex2DRGB(glm::vec2(x_bottom + width, y_left + height), glm::vec3(1.f,1.f,0.f));
	vertices[3] = glimac::Vertex2DRGB(glm::vec2(x_bottom, y_left + height), glm::vec3(0.f,0.f,1.f));
	
	setVBO();
	setVAO();
}

Button2D::~Button2D(){
	std::cout << "je free  le button" << std::endl;
}

const glimac::Vertex2DRGB* Button2D::getVertices() const{
	return vertices;
}

void Button2D::setVBO(){
	vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
}

void Button2D::setVAO(){
	vao.enableVertexAttribArray(0);
	vao.enableVertexAttribArray(1);
	vao.vertexAttribPointer(vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DRGB), (const GLvoid*) (0 * sizeof(GLfloat)) );
	vao.vertexAttribPointer(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DRGB), (const GLvoid*) (2 * sizeof(GLfloat)) );
}

void Button2D::draw() const{
	vao.bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	vao.unbind();
}

void Button2D::updateState(){
	//TO DO
}
