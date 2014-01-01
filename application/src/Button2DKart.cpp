#include "Button2DKart.hpp"

Button2DKart::Button2DKart()
  :Button2D::Button2D(){}

Button2DKart::Button2DKart(const float x_bottom, const float y_left, const float width, const float height, std::string pathTextureNoSelect, std::string pathTextureSelect, std::string nameOfButton, std::vector<std::string> descriptionKart, int numeroOfTheButton)
  :Button2D::Button2D(x_bottom, y_left, width, height, pathTextureNoSelect, pathTextureSelect, nameOfButton){
  	std::string descriptionKartTotal = "Acceleration : " + descriptionKart[0];
  	Texte2D* acceleration = new Texte2D(descriptionKartTotal);
  	float n_x_bottom = numeroOfTheButton * 240 + 40.f;
  	float n_y = 260.f;
  	acceleration->setPosition(n_x_bottom, n_y, 12);
  	generatedText.push_back(acceleration);

  	descriptionKartTotal = "Vitesse : " + descriptionKart[1];
  	Texte2D* speed = new Texte2D(descriptionKartTotal);
  	n_x_bottom = numeroOfTheButton * 240 + 40.f;
  	n_y = 240.f;
  	speed->setPosition(n_x_bottom, n_y, 12);
  	generatedText.push_back(speed);

  	descriptionKartTotal = "Poids : " + descriptionKart[2];
  	Texte2D* weight = new Texte2D(descriptionKartTotal);
  	n_x_bottom = numeroOfTheButton * 240 + 40.f;
  	n_y = 220.f;
  	weight->setPosition(n_x_bottom, n_y, 12);
  	generatedText.push_back(weight);
  }

Button2DKart::~Button2DKart(){
	if (ownership)
  {
  	for(unsigned int i = 0; i < generatedText.size(); ++i){
    	delete generatedText[i];
  	}
  }
}

void Button2DKart::draw(const glimac::ShaderProgram& shaderProgram) const{
	vao.bind();
	GLint locationUTexture = shaderProgram.getUniformIndex("uTexture");
	GLint locationUMat = shaderProgram.getUniformIndex("uModelMatrix");
    shaderProgram.setUniform(locationUTexture, 0);
    shaderProgram.setUniform(locationUMat, glm::mat3(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,1)));
	activTexture->bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	activTexture->unbind();
	vao.unbind();
}

void Button2DKart::update(){
	//Changer la texture associée 
	activTexture = tabTexture[1];
	if(model->isSelected())
	{
		activTexture = tabTexture[0];
	}
	setVBO();
}
