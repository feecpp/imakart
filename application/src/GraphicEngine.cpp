#include "GraphicEngine.hpp"
#include "program.hpp"
#include "TextFile.hpp"
#include <GL/glew.h>
#include <iostream>
#include "Object3D.hpp"

GraphicEngine::~GraphicEngine()
{
  //Le graphic engine delete tous ses objets 3D à sa mort
  //Utiliser un iterator déclenche un bug hyper chelou (tente de détruire un deuxième
  //pointeur vers la classe mère...)
  for (size_t i = 0; i < objects3D.size(); ++i)
  {
    delete objects3D[i];
  }
}

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

  glimac::Program program;
	program = glimac::loadProgram("shaders/Color2d.vs.glsl", "shaders/Color2d.fs.glsl");
  program.use();


  //SHADER STUFF JN(test du KartCube)
  //glimac::Program jnProgramTest = glimac::loadProgram("shaders/Simple3DVS.glsl", "shaders/SimpleFS.glsl");
  //jnProgramTest.use();
	
  return true;
}

void GraphicEngine::swapBuffers()
  {SDL_GL_SwapBuffers();}

void GraphicEngine::renderFrame(GameEngine* gameEngine)
{
  // Rendering code goes here
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  gameEngine->getMenu().draw();

  //Dessin des objets 3D test
  /*
  std::vector<Object3D* >::iterator one3DObject;
  for (one3DObject = objects3D.begin(); one3DObject != objects3D.end(); ++one3DObject)
  {
    (*one3DObject)->update();
    (*one3DObject)->draw();
  }
  */
}
