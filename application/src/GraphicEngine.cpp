#include "GraphicEngine.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Object3D.hpp"
#include "Object2D.hpp"
#include <TextFile.hpp>
#include "Camera.hpp"
#include "Light.hpp"
#include "Skybox.hpp"
#include <cassert>
#include <SFML/OpenGL.hpp>

GraphicEngine::GraphicEngine()
  : currentCamera(nullptr), currentLight(nullptr), skybox(nullptr), currentProgram(nullptr), menuProgram(nullptr), raceProgram(nullptr), texte2DProgram(nullptr), skyboxProgram(nullptr)
{
}

GraphicEngine::~GraphicEngine()
{
  //Le graphic engine delete tous ses objets 3D Ã   sa mort
  reset();

  delete menuProgram;
  delete raceProgram;
  delete texte2DProgram;
  delete skyboxProgram;
  delete currentCamera;
  delete currentLight;
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
  
  //Initialisation des shader programs
  initShaderPrograms();

  skybox = new Skybox(currentCamera);
  if(skybox->init("textures/skybox","posx.jpg","negx.jpg","posy.jpg","negy.jpg","posz.jpg","negz.jpg")){
    std::cout << "Valeur gluint de la skybox : " << skybox->getCubeMapTexture()->getTextureObj() << std::endl;
  }else{
    std::cerr << "Impossible d'initialiser la skybox" << std::endl;
  }

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

  //En attendant une meilleure gestion de la camÃ©ra dans le menu,
  //menu => camera == nullptr
  if (currentCamera != nullptr)
  {
    //Mise Ãƒ  jour matrice ViewProjection
    //Attention : le vertex shader doit contenir les bonnes uniforms
    currentCamera->updateViewProjectionMatrix();
    const glm::mat4& viewMatrix = currentCamera->getViewMatrix();
    const glm::mat4& normalMatrix = glm::transpose(glm::inverse(currentCamera->getViewMatrix()));
    const glm::mat4& viewProjection = currentCamera->getViewProjectionMatrix();
    GLint viewId = currentProgram->getUniformIndex("uView");
    GLint viewProjectionId = currentProgram->getUniformIndex("viewProjection");
    GLint normalId = currentProgram->getUniformIndex("uNormal");
    currentProgram->setUniform(viewId, viewMatrix);
    currentProgram->setUniform(normalId, normalMatrix);
    currentProgram->setUniform(viewProjectionId, viewProjection);
  }

  //Gestion de la lumiÃ¨re
  if (currentLight != nullptr)
  {
    const glm::mat4& viewMatrix = currentCamera->getViewMatrix();
   // currentLight->updateLightDirection(viewMatrix);
    const glm::vec3& direction = currentLight->getLighDirection();
    const glm::vec3& intensity = currentLight->getLightIntensity();
    GLint lightDirId = currentProgram->getUniformIndex("uLightDir");
    GLint lightIntensityId = currentProgram->getUniformIndex("uLi");
    glUniform3fv(lightDirId,1, glm::value_ptr(direction)); // A MODIFIER --> faire appel Ã  une fonction dans ShaderProgram
    currentProgram->setUniform(lightIntensityId, intensity);
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

  if (skybox != nullptr && currentProgram == raceProgram)
  {
    useSkyboxProgram();
    const glm::mat4& viewProjection = currentCamera->getViewProjectionMatrix();
    GLint viewProjectionId = currentProgram->getUniformIndex("viewProjection");
    currentProgram->setUniform(viewProjectionId, viewProjection);
    skybox->render(*currentProgram);
    useRaceProgram();
  }

  if (currentProgram == raceProgram){
    useTexteProgram();
    if(chrono->getModel() != nullptr)
      chrono->update();
    chrono->printTexte2D(10, 570, 20, *currentProgram);
    useRaceProgram();
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

  //Pour le dessin du texte 2D
  texte2DProgram = new glimac::ShaderProgram();
  texte2DProgram->addShader(GL_VERTEX_SHADER, "shaders/texte2D.vs.glsl");
  texte2DProgram->addShader(GL_FRAGMENT_SHADER, "shaders/texte2D.fs.glsl");
  if (!texte2DProgram->compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
  }

  //Pour la skybox 
  skyboxProgram = new glimac::ShaderProgram();
  skyboxProgram->addShader(GL_VERTEX_SHADER, "shaders/Skybox.vs.glsl");
  skyboxProgram->addShader(GL_FRAGMENT_SHADER, "shaders/Skybox.fs.glsl");
  if (!skyboxProgram->compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
  }
}

void GraphicEngine::reset()
{
  //Utiliser un iterator dÃ©clenche un bug hyper chelou (tente de dÃ©truire un deuxiÃ¨me
  //pointeur vers la classe mÃ¨re...)
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

void GraphicEngine::setLight(Light* newLight){
    delete currentLight;
    currentLight = newLight;
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

void GraphicEngine::useTexteProgram()
{
  texte2DProgram->use();
  currentProgram = texte2DProgram;
}

void GraphicEngine::useSkyboxProgram()
{
  skyboxProgram->use();
  currentProgram = skyboxProgram;
}
