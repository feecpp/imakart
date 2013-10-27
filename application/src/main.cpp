#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Button2D.hpp"
#include "ButtonLogic.hpp"
#include "program.hpp"
#include "Checkpoint.hpp"
#include "Map.hpp"
//#include "ShaderProgram.hpp"
#include "Application.hpp"
#include "Menu.hpp"

static const Uint32 FPS = 30;
static const Uint32 FRAME_DURATION = 1000.f / FPS;

static const Uint32 WINDOW_WIDTH = 800;
static const Uint32 WINDOW_HEIGHT = 600;
static const Uint32 WINDOW_BPP = 32;

int main() {
/*
  // Pour le "vrai jeu"
  Application app;
  app.setupEverything();
  app.startGame();
  return EXIT_SUCCESS;
*/

	// Pour les tests
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Unable to initialize SDL" << std::endl;
		return EXIT_FAILURE;
	}

	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, SDL_OPENGL)) {
		std::cerr << "Unable to open the window and get an OpenGL context" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_WM_SetCaption("OpenGL4Imacs", NULL);

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
		return EXIT_FAILURE;
	}
	
	Menu main_menu(2);
	ButtonLogic jouer2("jouer", -0.5, -0.8, 0.5, 0.2);
	main_menu.add_button(jouer2);
	ButtonLogic jouer("jouer", -0.2, 0.1, 0.5, 0.2);
	main_menu.add_button(jouer);
	
	// Load des shaders méthode JN
  /*glimac::ShaderProgram program;
	program.addShader(GL_VERTEX_SHADER, "shaders/Color2d.vs.glsl");
	program.addShader(GL_FRAGMENT_SHADER, "shaders/Color2d.fs.glsl");
	std::string debug;
	program.compileAndLinkShaders(debug);
	std::cout << debug << std::endl;
  program.useProgram();*/
	
	// Load des shaders méthode Laurent Noel
  glimac::Program program;
	program = glimac::loadProgram("shaders/Color2d.vs.glsl", "shaders/Color2d.fs.glsl");
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

	
	bool done = false;
	while(!done) {
		Uint32 tStart = SDL_GetTicks();
		
		// Rendering code goes here
		glClear(GL_COLOR_BUFFER_BIT);
		
		main_menu.draw();
		// Application code goes here

		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				default:
					break;
				case SDL_QUIT:
					done = true;
					break;
			}
		}

		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		SDL_GL_SwapBuffers();

		Uint32 tEnd = SDL_GetTicks();
		Uint32 d = tEnd - tStart;
		if(d < FRAME_DURATION) {
			SDL_Delay(FRAME_DURATION - d);
		}
	}
	// Destruction des ressources
	SDL_Quit();

	return EXIT_SUCCESS;
}
