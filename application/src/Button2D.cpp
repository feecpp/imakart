#include "Button2D.hpp"
#include <iostream>

Button2D::Button2D(){
	glm::vec3 color(1.f,0.f,0.f);
	vertices[0] = glimac::Vertex2DRGB(glm::vec2(-0.5f, -0.5f), color);
	vertices[1] = glimac::Vertex2DRGB(glm::vec2(0.5f, -0.5f), color);
	vertices[2] = glimac::Vertex2DRGB(glm::vec2(0.5f, 0.5f), color);
	vertices[3] = glimac::Vertex2DRGB(glm::vec2(-0.5f, 0.5f), color);
	
	setVBO();
	setVAO();
}

Button2D::Button2D(const float x_bottom, const float y_left, const float width, const float height){
	glm::vec3 color(1.f,0.f,0.f);

	vertices[0] = glimac::Vertex2DRGB(glm::vec2(x_bottom, y_left), color);
	vertices[1] = glimac::Vertex2DRGB(glm::vec2(x_bottom + width, y_left), color);
	vertices[2] = glimac::Vertex2DRGB(glm::vec2(x_bottom + width, y_left + height), color);
	vertices[3] = glimac::Vertex2DRGB(glm::vec2(x_bottom, y_left + height), color);

	setVBO();
	setVAO();
}

Button2D::~Button2D(){
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

void Button2D::draw(){
	/*
	if( model->isSelected() ){
		updateState();
	}*/
	vao.bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	vao.unbind();
}

void Button2D::updateState(){
	glm::vec3 color(1.f,0.f,0.f);
	if(vertices[0].color[0] == 1)
		glm::vec3 color(0.f,1.f,0.f);
	
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;
	
	setVBO();
}
