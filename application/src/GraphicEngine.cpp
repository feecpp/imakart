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

sf::RenderWindow& GraphicEngine::init()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "ImaKart");

  GLenum glewCode = glewInit();
  if(GLEW_OK != glewCode) {
    std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
    return false;
  }

  //OpenGL initial state
  glEnable(GL_DEPTH_TEST);
  
  //Initialisation des shader programs
  initShaderPrograms();
	
  return window;
}

void GraphicEngine::swapBuffers(sf::RenderWindow& window)
  {window.display();}

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
    (*one3DObject)->draw();
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
}

void GraphicEngine::useMenuProgram() const
{
  menuProgram->use();
}

void GraphicEngine::useRaceProgram() const
{
  raceProgram->use();
}
