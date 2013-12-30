#ifndef BUTTONKART_HPP
#define BUTTONKART_HPP

#include "Button2D.hpp"
#include <string>

class Button2DKart : public Button2D
{
public:
	Button2DKart(); // Unit square
	Button2DKart(const float x_bottom, const float y_left, const float width, const float height, std::string pathTextureNoSelect, std::string pathTextureSelect, std::string nameOfButton, std::vector<std::string> descriptionKart, int numeroOfTheButton); 
	~Button2DKart();
	
	void draw(const glimac::ShaderProgram& shaderProgram) const;
	void update();

private:
};

#endif // BUTTON_HPP
