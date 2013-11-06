#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Button2D.hpp"
#include "ButtonLogic.hpp"
#include "ShaderProgram.hpp"
#include "Checkpoint.hpp"
#include "Map.hpp"
//#include "ShaderProgram.hpp"
#include "Application.hpp"



int main() {

  // Pour le "vrai jeu"
  Application app;
  sf::RenderWindow& window = app.setupEverything();
  app.startGame(window);
  return EXIT_SUCCESS;


	// Pour les tests
  /*  sf::RenderWindow window(sf::VideoMode(800, 600), "ImaKart");

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
		return EXIT_FAILURE;
    }*/
	/*
	Menu main_menu;
	main_menu.create_main_menu();
	*/
	// Load des shaders méthode JN
  /*glimac::ShaderProgram program;
	program.addShader(GL_VERTEX_SHADER, "shaders/Color2d.vs.glsl");
	program.addShader(GL_FRAGMENT_SHADER, "shaders/Color2d.fs.glsl");
	std::string debug;
	program.compileAndLinkShaders(debug);
	std::cout << debug << std::endl;
  program.useProgram();*/
	
	// Load des shaders méthode Laurent Noel
  glimac::ShaderProgram program;
  program = glimac::ShaderProgram::loadProgram("shaders/Color2d.vs.glsl", "shaders/Color2d.fs.glsl");
	program.use();
  
  /* //Code pour tester la classe Map
  Map map;
  map.loadData("./maps/carte1.map"); //a voir si le chemin fonctionne aussi chez vous. Sous windows je ne peux pas prendre l'architecture telle qu'elle est sur GitHub

  std::cout <<std::endl << "--- LOADING RECAP ---"<< std::endl;
  std::cout <<"Name: " << map.getName() << std::endl;
  std::cout << "width: " << map.getWidth() << std::endl;
  std::cout << "height: " << map.getHeight() << std::endl;
  std::cout << "altitude: " << map.getAltitude() << std::endl;

  std::vector<Checkpoint> checkpoints = map.getCheckpoints();
  for(unsigned int i =0; i< checkpoints.size(); ++i){
       std::cout << "checkpoint n"<< i << " : (origin) x=" << checkpoints[i].getOrigin().x<< " y=" << checkpoints[i].getOrigin().y << " z=" << checkpoints[i].getOrigin().z << std::endl;
  }

  std::cout <<"Start is at : (origin) x=" << map.getStart().getOrigin().x << " y=" << map.getStart().getOrigin().y << " z=" << map.getStart().getOrigin().z << std::endl;
  std::cout <<"If different, end is at : (origin) x=" << map.getEnd().getOrigin().x << " y=" << map.getEnd().getOrigin().y << " z=" << map.getEnd().getOrigin().z << std::endl;
  std::cout << "Is it completed ? " << map.isCompleted() << std::endl;*/

	
    //bool done = false;
    //while(!done) {

		// Rendering code goes here
        //glClear(GL_COLOR_BUFFER_BIT);
	
		// Application code goes here

		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
        //SDL_GL_SwapBuffers();
    //}
	// Destruction des ressources
    //window.close();

	return EXIT_SUCCESS;
}
