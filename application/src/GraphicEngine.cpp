#include "GraphicEngine.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <TextFile.hpp>
#include "Camera.hpp"
#include <cassert>
#include <SFML/OpenGL.hpp>
#include "Interface.hpp"

GraphicEngine::GraphicEngine()
  : world3D(nullptr), interface(nullptr), motionBlur(nullptr), motionBlurEnabled(false), loadingScreen(nullptr), loadingScreenTexture(nullptr),
    loadingScreenEnabled(false)
{
}

GraphicEngine::~GraphicEngine()
{
  reset();
  delete motionBlur;
  delete loadingScreen;
  delete loadingScreenTexture;
  delete screenquad;
  delete screenquadData;
}

sf::RenderWindow& GraphicEngine::init()
{
  sf::ContextSettings sfmlSettings;
  sfmlSettings.antialiasingLevel = settings.ANTIALIAS_LEVEL;
  sfmlSettings.depthBits = 24;
  sfmlSettings.stencilBits = 8;
  sfmlSettings.majorVersion = 3;
  sfmlSettings.minorVersion = 3;

  (this->window).create(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "ImaKart : Minions Karts", sf::Style::Default, sfmlSettings);
  sf::RenderWindow& myWindow = window;

  window.setFramerateLimit(settings.FPS);

  GLenum glewCode = glewInit();
  if(GLEW_OK != glewCode) {
    std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
    return window;
  }

  delete motionBlur;
  motionBlur = new MotionBlur(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT);

  //Loading screen
  delete loadingScreenTexture;
  loadingScreenTexture = new glimac::Texture(GL_TEXTURE_2D);
  loadingScreenTexture->loadTexture2D("textures/loading_screen.png");
  screenquad = new glimac::VAO();
  screenquadData = new glimac::LowLevelVBO();
  glm::vec2 quad[4];
  quad[0] = glm::vec2(-1.f, -1.f);
  quad[1] = glm::vec2(-1.f, 1.f);
  quad[2] = glm::vec2(1.f, 1.f);
  quad[3] = glm::vec2(1.f, -1.f);
  screenquadData->setBufferData(glm::value_ptr(quad[0]), 4 * sizeof(glm::vec2), GL_STATIC_DRAW);
  screenquad->enableVertexAttribArray(0);
  screenquad->vertexAttribPointer(*screenquadData, 0, 2, GL_FLOAT, GL_TRUE, 0, (const GLvoid* ) NULL);

  delete loadingScreen;
  loadingScreen = new glimac::ShaderProgram();
  loadingScreen->addShader(GL_VERTEX_SHADER, "shaders/motionBlurVS.glsl");
  loadingScreen->addShader(GL_FRAGMENT_SHADER, "shaders/LoadingScreenFS.glsl");
  std::string logInfo;
  if (!loadingScreen->compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
    assert(false);
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

  world3D->draw();
  interface->update();
  interface->draw();

  if (motionBlurEnabled)
    motionBlur->renderFrame();
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

void GraphicEngine::showLoadingScreen()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  GLuint tex0ID = loadingScreen->getUniformIndex("textureUnit0");
  loadingScreen->setUniform(tex0ID, 0);
  glActiveTexture(GL_TEXTURE0);
  loadingScreen->use();
  loadingScreenTexture->bind();
  screenquad->bind();
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  screenquad->unbind();
  swapBuffers();
}
