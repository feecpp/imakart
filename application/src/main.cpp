#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Button2D.hpp"
<<<<<<< HEAD
#include "program.hpp"
//#include "ShaderProgram.hpp"
=======
>>>>>>> 2c7adfefc05d84bf0a7359b7ecba3c0424d9aafc

static const Uint32 FPS = 30;
static const Uint32 FRAME_DURATION = 1000.f / FPS;

static const Uint32 WINDOW_WIDTH = 800;
static const Uint32 WINDOW_HEIGHT = 600;
static const Uint32 WINDOW_BPP = 32;

int main() {
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
	
	Button2D jouer(-0.5,-0.8,0.5,0.2);

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
	
	
	bool done = false;
	while(!done) {
		Uint32 tStart = SDL_GetTicks();
		
		// Rendering code goes here
		glClear(GL_COLOR_BUFFER_BIT);
		
		jouer.draw();
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
