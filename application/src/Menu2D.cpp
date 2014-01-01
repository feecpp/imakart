#include "Menu2D.hpp"
#include "Button2DKart.hpp"
#include "Hangar.hpp"
#include "Kart.hpp"
#include "convert.hpp"

Menu2D::Menu2D():
	nbButtonInMenu(0){
		vertices[0] = glimac::Vertex2DUV(glm::vec2(-1.f, -1.f), glm::vec2(0,1));
		vertices[1] = glimac::Vertex2DUV(glm::vec2(1.f, -1.f), glm::vec2(1,1));
		vertices[2] = glimac::Vertex2DUV(glm::vec2(1.f, 1.f), glm::vec2(1,0));
		vertices[3] = glimac::Vertex2DUV(glm::vec2(-1.f, 1.f), glm::vec2(0,0));

		glimac::Texture* background = new glimac::Texture(GL_TEXTURE_2D);
		background->loadTexture2D("textures/menu/homePage.jpg");
		tabTexture.push_back(background);
		activTexture = tabTexture[0];

		setVBO();
		setVAO();
	}

Menu2D* Menu2D::initialiseMainMenu(){
	
	Menu2D* mainMenu = new Menu2D;
	
	Button2D* jouer = new Button2D(-0.3, 0.3, 0.6, 0.2, "textures/menu/jouer.png", "textures/menu/jouerSelect.png", "jouer");
	Button2D* options = new Button2D(-0.3, 0.0, 0.6, 0.2, "textures/menu/options.png", "textures/menu/optionsSelect.png", "options");
	Button2D* quitter = new Button2D(-0.3, -0.3, 0.6, 0.2, "textures/menu/quitter.png", "textures/menu/quitterSelect.png", "quitter");

	mainMenu->addButton(jouer);
	mainMenu->addButton(options);
	mainMenu->addButton(quitter);

	return mainMenu;
}

Menu2D* Menu2D::initialiseKartMenu(std::vector <std::string> kartsName){
	Menu2D* kartMenu = new Menu2D;
	for(unsigned int i = 0; i < kartsName.size(); ++i){
		std::string textures = "textures/karts/";
		textures = textures + kartsName[i];
		std::string texturesS = textures + "Selected.jpg";
		textures = textures + ".jpg";
		Specifications spe = Hangar::getSingletonHangar()->getKartByName(kartsName[i]).specifications;
		std::vector<std::string> caracteristique;
		caracteristique.push_back(glimac::convertToString(spe.acceleration));
		caracteristique.push_back(glimac::convertToString(spe.maxSpeed));
		caracteristique.push_back(glimac::convertToString(spe.weight));
    Button2DKart* kart = new Button2DKart(- 0.9 + i * 0.6, 0.05, 0.5, 0.5, textures, texturesS, kartsName[i], caracteristique, i);
		kartMenu->addButton(kart);
	}

	return kartMenu;
}

Menu2D* Menu2D::initialiseMapMenu(){
	Menu2D* mapMenu = new Menu2D;

	return mapMenu;
}

void Menu2D::addButton(Button2D* buttonToAdd){
		tab2DMenu.push_back(buttonToAdd);
		++nbButtonInMenu;
}

void Menu2D::update(){
	for(unsigned int i = 0; i < nbButtonInMenu; ++i){
		tab2DMenu[i]->update();
	}
}

void Menu2D::draw(const glimac::ShaderProgram& shaderProgram) const{

	for(unsigned int i = 0; i < nbButtonInMenu; ++i){
		tab2DMenu[i]->draw(shaderProgram);
	}
	
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

void Menu2D::setVBO(){
	vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
}

void Menu2D::setVAO(){
	vao.enableVertexAttribArray(0);
	vao.enableVertexAttribArray(1);
	vao.vertexAttribPointer(vbo, 0, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (0 * sizeof(GLfloat)) );
	vao.vertexAttribPointer(vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DUV), (const GLvoid*) (2 * sizeof(GLfloat)) );
}

Menu2D::~Menu2D(){
	for (size_t i = 0; i < tab2DMenu.size(); ++i)
	{
	  delete tab2DMenu[i];
	}
	tab2DMenu.clear();
}
