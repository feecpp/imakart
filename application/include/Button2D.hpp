#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Object2D.hpp"
#include "Texte2D.hpp"
#include "VBO.hpp"
#include "VAO.hpp"

#include <string>


class Button2D : public Object2D
{
public:
	Button2D(); // Unit square
	Button2D(const float x_bottom, const float y_left, const float width, const float height, std::string pathTextureNoSelect, std::string pathTextureSelect, std::string nameOfButton); 
	~Button2D();
	
	const glimac::Vertex2DUV* getVertices() const;
	void updateVertices(const float x_bottom, const float y_left, const float width, const float height);

	void draw(const glimac::ShaderProgram& shaderProgram) const;
	void update();
	
private:
	glimac::Vertex2DUV vertices[4];
	glimac::LowLevelVBO vbo;
	glimac::VAO vao;
	
	Texte2D myText;

	bool done;
	void setVBO(); //call in the constructor
	void setVAO(); //call in the constructor
};

#endif // BUTTON_HPP
