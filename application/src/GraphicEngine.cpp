#include "GraphicEngine.hpp"
#include "TextFile.hpp"
#include <GL/glew.h>
#include <iostream>
#include "Object3D.hpp"
#include "Object2D.hpp"
#include "TextFile.hpp"

GraphicEngine::~GraphicEngine()
{
  //Le graphic engine delete tous ses objets 3D à sa mort
  reset();

  delete menuProgram;
  delete raceProgram;
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
  
  //Initialisation des shader programs
  initShaderPrograms();
	
  return true;
}

void GraphicEngine::swapBuffers()
  {SDL_GL_SwapBuffers();}

void GraphicEngine::renderFrame()
{
  // Rendering code goes here

  //Dessin des objets 2D
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for(unsigned int i = 0 ; i < objects2D.size() ; ++i){
	  objects2D[i]->update();
	  objects2D[i]->draw();
  }

  //Dessin des objets 3D test
  std::vector<Object3D* >::iterator one3DObject;
  for (one3DObject = objects3D.begin(); one3DObject != objects3D.end(); ++one3DObject)
  {
    (*one3DObject)->update();
    (*one3DObject)->draw(*raceProgram);
  }

}

void GraphicEngine::initShaderPrograms()
{

  //Pour le dessin du menu
  menuProgram = new glimac::ShaderProgram();
  menuProgram->addShader(GL_VERTEX_SHADER, "shaders/Color2d.vs.glsl");
  menuProgram->addShader(GL_FRAGMENT_SHADER, "shaders/Color2d.fs.glsl");
  std::string logInfo;
  if (!menuProgram->compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
  }
  menuProgram->use();

  //Pour le dessin du monde 3D
  raceProgram = new glimac::ShaderProgram();
  raceProgram->addShader(GL_VERTEX_SHADER, "shaders/Simple3DVS.glsl");
  raceProgram->addShader(GL_FRAGMENT_SHADER, "shaders/SimpleFS.glsl");
  if (!raceProgram->compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
  }
}

void GraphicEngine::reset()
{
  //Utiliser un iterator déclenche un bug hyper chelou (tente de détruire un deuxième
  //pointeur vers la classe mère...)
  for (size_t i = 0; i < objects3D.size(); ++i)
  {
    delete objects3D[i];
  }

  for (size_t i = 0; i < objects2D.size(); ++i)
  {
    delete objects2D[i];
  }
  objects3D.erase(objects3D.begin(), objects3D.end());
  objects2D.erase(objects2D.begin(), objects2D.end());
}

void GraphicEngine::useMenuProgram() const
{
  menuProgram->use();
}

void GraphicEngine::useRaceProgram() const
{
  raceProgram->use();
}
