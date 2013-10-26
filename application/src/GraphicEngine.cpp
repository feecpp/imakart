#include "GraphicEngine.hpp"

#include <GL/glew.h>
#include <iostream>


bool GraphicEngine::init()
{
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Unable to initialize SDL" << std::endl;
    return false;
  }

  if(NULL == SDL_SetVideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT, settings.WINDOW_BPP, SDL_OPENGL)) {
    std::cerr << "Unable to open the window and get an OpenGL context" << std::endl;
    return false;
  }

  SDL_WM_SetCaption("Imakart", NULL);

  GLenum glewCode = glewInit();
  if(GLEW_OK != glewCode) {
    std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
    return false;
  }

  //OpenGL initial state
  glEnable(GL_DEPTH_TEST);

  return true;
}

void GraphicEngine::swapBuffers()
  {SDL_GL_SwapBuffers();}

void GraphicEngine::renderFrame()
{
  // Rendering code goes here
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
