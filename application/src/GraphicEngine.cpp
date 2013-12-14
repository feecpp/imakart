#include "GraphicEngine.hpp"
#include <GL/glew.h>
#include <iostream>
#include "Object3D.hpp"
#include "Object2D.hpp"
#include <TextFile.hpp>
#include "Camera.hpp"
#include <cassert>
#include <SFML/OpenGL.hpp>

GraphicEngine::GraphicEngine()
  : currentCamera(nullptr), currentProgram(nullptr), menuProgram(nullptr), raceProgram(nullptr)
{
}

GraphicEngine::~GraphicEngine()
{
  //Le graphic engine delete tous ses objets 3D �  sa mort
  reset();

  delete menuProgram;
  delete raceProgram;
  delete currentCamera;
}

sf::RenderWindow& GraphicEngine::init()
{
  (this->window).create(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "ImaKart");

  sf::RenderWindow& myWindow = window;

  window.setFramerateLimit(settings.FPS);
  GLenum glewCode = glewInit();
  if(GLEW_OK != glewCode) {
    std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
    return window;
  }

  //OpenGL initial state
  glEnable(GL_DEPTH_TEST);
  glClearColor(1.f, 1.f, 1.f, 1.f);

  //Initialisation des textures
  initTextures();
  
  //Initialisation des shader programs
  initShaderPrograms();

  //Initialisation de la font
  if (!font.loadFromFile("fonts/arialPixel.ttf"))
  {
    std::cerr << "Unable to initialize FONT " << std::endl;
  }

  return myWindow;
}

void GraphicEngine::swapBuffers()
  {window.display();}

const GraphicSettings&GraphicEngine::getSettings() const
{
  return settings;
}

void GraphicEngine::renderFrame()
{
  assert(currentProgram != nullptr);
  //assert(currentCamera != nullptr);

  //En attendant une meilleure gestion de la caméra dans le menu,
  //menu => camera == nullptr
  if (currentCamera != nullptr)
  {
    //Mise �  jour matrice ViewProjection
    //Attention : le vertex shader doit contenir les bonnes uniforms
    currentCamera->updateViewProjectionMatrix();
    const glm::mat4& viewProjection = currentCamera->getViewProjectionMatrix();
    GLint viewProjectionId = currentProgram->getUniformIndex("viewProjection");
    currentProgram->setUniform(viewProjectionId, viewProjection);
  }

  //Dessin des objets 2D
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for(unsigned int i = 0 ; i < objects2D.size() ; ++i){
	  objects2D[i]->update();

	  objects2D[i]->draw(*currentProgram);
  }

  //Dessin des objets 3D
  std::vector<Object3D* >::iterator one3DObject;
  for (one3DObject = objects3D.begin(); one3DObject != objects3D.end(); ++one3DObject)
  {
    (*one3DObject)->update();
    //Attention : le vertex shader doit contenir les bonnes uniforms
    (*one3DObject)->draw(*currentProgram);
  }

}

void GraphicEngine::initShaderPrograms()
{

  //Pour le dessin du menu
  menuProgram = new glimac::ShaderProgram();
  menuProgram->addShader(GL_VERTEX_SHADER, "shaders/tex2D.vs.glsl");
  menuProgram->addShader(GL_FRAGMENT_SHADER, "shaders/tex2D.fs.glsl");
  std::string logInfo;
  if (!menuProgram->compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
  }

  useMenuProgram();

  //Pour le dessin du monde 3D
  raceProgram = new glimac::ShaderProgram();
  raceProgram->addShader(GL_VERTEX_SHADER, "shaders/Simple3DVS.glsl");
  raceProgram->addShader(GL_FRAGMENT_SHADER, "shaders/SimpleFS.glsl");
  if (!raceProgram->compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
  }
}

GLuint LoadTexture(std::string filename)
{
  GLuint idTexture;

  sf::Image image;
  if(image.loadFromFile(filename))
  {
    glGenTextures(1,&idTexture);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  return idTexture;
}

void GraphicEngine::initTextures()
{
  //Pour le menu
  tabTextures.push_back(LoadTexture("textures/jouer.png"));   
  tabTextures.push_back(LoadTexture("textures/jouerSelect.png"));   
  tabTextures.push_back(LoadTexture("textures/options.png"));   
  tabTextures.push_back(LoadTexture("textures/optionsSelect.png"));   
  tabTextures.push_back(LoadTexture("textures/credits.png"));   
  tabTextures.push_back(LoadTexture("textures/creditsSelect.png"));   
  tabTextures.push_back(LoadTexture("textures/quitter.png"));   
  tabTextures.push_back(LoadTexture("textures/quitterSelect.png"));   
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

void GraphicEngine::setCamera(Camera* newCamera)
{
  delete currentCamera;
  currentCamera = newCamera;
}

void GraphicEngine::useMenuProgram()
{
  menuProgram->use();
  currentProgram = menuProgram;
}

void GraphicEngine::useRaceProgram()
{
  raceProgram->use();
  currentProgram = raceProgram;
}
