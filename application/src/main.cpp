#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Button.hpp"

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
	
	Button jouer(-1,-1,0.5,0.2);
	
	// Initialisation VBO
	glimac::LowLevelVBO vbo(jouer.getVertices(), 8 * sizeof(GLfloat), GL_STATIC_DRAW, GL_ARRAY_BUFFER);

	// Initialisation VAO
	glimac::VAO vao;
	// Binder le vao
	vao.bind();

	glEnableVertexAttribArray(0);
	// Binder le vbo
	vbo.bind();
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const GLvoid*) (0 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Debinder le vao
	glBindVertexArray(0);

	bool done = false;
	while(!done) {
		Uint32 tStart = SDL_GetTicks();
		
		// Rendering code goes here
		glClear(GL_COLOR_BUFFER_BIT);
		
		vao.bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
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
