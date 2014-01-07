#include "GraphicEngine.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <TextFile.hpp>
#include "Camera.hpp"
#include "Light.hpp"
#include <cassert>
#include <SFML/OpenGL.hpp>
#include "Interface.hpp"

GraphicEngine::GraphicEngine()
  : world3D(nullptr), interface(nullptr), motionBlur(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT)
{
}

GraphicEngine::~GraphicEngine()
{
  reset();
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
  glClearColor(0.7f, 0.7f, 0.7f, 1.7f);

  return myWindow;
}

void GraphicEngine::swapBuffers()
  {window.display();}

const GraphicSettings&GraphicEngine::getSettings() const
{
  return settings;
}

void GraphicEngine::setNewSizeWindow(const unsigned int width, const unsigned int height){
  settings.WINDOW_WIDTH = width;
  settings.WINDOW_HEIGHT = height;
}

void GraphicEngine::renderFrame()
{
  //Il existe toujours un World3D meme dans le menu (il fait rien actuellement)
  assert(world3D && interface);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  std::cout << "--------------------------" << std::endl;
  world3D->draw();
  interface->update();
  interface->draw();
  motionBlur.renderFrame();

}

void GraphicEngine::setCurrentWorld3D(World3D* newWorld3D)
{
  delete world3D;
  world3D = newWorld3D;
  world3D->init();
}

void GraphicEngine::setCurrentInterface(Interface* newInterface)
{
  delete interface;
  interface = newInterface;
  interface->init();
}

World3D* GraphicEngine::getWorld3D(){ 
  return world3D;
}

sf::RenderWindow& GraphicEngine::getWindow(){
  return window;
}

void GraphicEngine::reset()
{
  delete world3D;
  delete interface;
  interface = nullptr;
  world3D = nullptr;
}
