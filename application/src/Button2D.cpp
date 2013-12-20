#include "Button2D.hpp"

Button2D::Button2D()
	:myText()
{
	vertices[0] = glimac::Vertex2DUV(glm::vec2(-0.5f, -0.5f), glm::vec2(0,1));
	vertices[1] = glimac::Vertex2DUV(glm::vec2(0.5f, -0.5f), glm::vec2(1,1));
	vertices[2] = glimac::Vertex2DUV(glm::vec2(0.5f, 0.5f), glm::vec2(1,0));
	vertices[3] = glimac::Vertex2DUV(glm::vec2(-0.5f, 0.5f), glm::vec2(0,0));

	setVBO();
	setVAO();
}

Button2D::Button2D(const float x_bottom, const float y_left, const float width, const float height, std::string pathTextureNoSelect, std::string pathTextureSelect, std::string nameOfButton)
	:myText(nameOfButton)
{
	vertices[0] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left), glm::vec2(0,1));
	vertices[1] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left), glm::vec2(1,1));
	vertices[2] = glimac::Vertex2DUV(glm::vec2(x_bottom + width, y_left + height), glm::vec2(1,0));
	vertices[3] = glimac::Vertex2DUV(glm::vec2(x_bottom, y_left + height), glm::vec2(0,0));

	glimac::Texture* first = new glimac::Texture(GL_TEXTURE_2D);
	first->loadTexture2D(pathTextureSelect);
	tabTexture.push_back(first);

	glimac::Texture* second = new glimac::Texture(GL_TEXTURE_2D);
	second->loadTexture2D(pathTextureNoSelect);
	tabTexture.push_back(second);

	activTexture = tabTexture[0];

	float n_x_bottom = x_bottom * 400.f + 400.f; //Pour mettre entre 0 et 800 (comme modifié apres dans le shader)
	float n_y = (y_left - 0.1f) * 300.f + 300.f;
	myText.setPosition(n_x_bottom, n_y, 20);

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
	GLint locationUMat = shaderProgram.getUniformIndex("uModelMatrix");
    shaderProgram.setUniform(locationUTexture, 0);
    shaderProgram.setUniform(locationUMat, glm::mat3(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,1))); 
	activTexture->bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	activTexture->unbind();
	vao.unbind();
}

void Button2D::update(){
	//Changer la texture associée 
	activTexture = tabTexture[1];
	if(model->isSelected())
	{
		activTexture = tabTexture[0];
	}
	setVBO();
}
