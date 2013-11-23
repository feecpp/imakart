#include "Button2D.hpp"
#include <iostream>

Button2D::Button2D()
{
	vertices[0] = glimac::Vertex2DUV(glm::vec2(-0.5f, -0.5f), glm::vec2(0,0));
	vertices[1] = glimac::Vertex2DUV(glm::vec2(0.5f, -0.5f), glm::vec2(1,0));
	vertices[2] = glimac::Vertex2DUV(glm::vec2(0.5f, 0.5f), glm::vec2(1,1));
	vertices[3] = glimac::Vertex2DUV(glm::vec2(-0.5f, 0.5f), glm::vec2(0,1));
	
	setVBO();
	setVAO();
}

Button2D::Button2D(const float x_bottom, const float y_left, const float width, const float height)
{
	vertices[0] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left), glm::vec2(0,0));
	vertices[1] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left), glm::vec2(1,0));
	vertices[2] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left + height), glm::vec2(1,1));
	vertices[3] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left + height), glm::vec2(0,1));

	setVBO();
	setVAO();
}

Button2D::~Button2D(){

}

const glimac::Vertex2DUV* Button2D::getVertices() const{
	return vertices;
}

void Button2D::setVBO(){
	vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
}

void Button2D::setVAO(){
	vao.enableVertexAttribArray(0);
	vao.enableVertexAttribArray(1);
	vao.vertexAttribPointer(vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (0 * sizeof(GLfloat)) );
	vao.vertexAttribPointer(vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (2 * sizeof(GLfloat)) );
}

void Button2D::draw(const glimac::ShaderProgram& shaderProgram) const{
	vao.bind();
	GLint locationUTexture = shaderProgram.getUniformIndex("uTexture");
    shaderProgram.setUniform(locationUTexture, 0); 
	glBindTexture(GL_TEXTURE_2D, idTexture);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	vao.unbind();
}

void Button2D::update(){
	//Changer la texture associée 
	setVBO();
}
