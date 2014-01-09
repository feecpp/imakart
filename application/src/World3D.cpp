#include "World3D.hpp"
#include "Object3D.hpp"
#include <stdexcept>
#include "Camera.hpp"
#include <iostream>


World3D::World3D(const unsigned int width, const unsigned int height)
    : camera(new Camera(width,height)), sun(new DirectionalLight()), ambientLight(0.3f,0.3f,0.3f,1.0f), spot(new SpotLight()) //Un peu degueu, a voir, c'est pour simplifier
{
  //Pour le dessin du monde 3D
  raceProgram.addShader(GL_VERTEX_SHADER, "shaders/Simple3DVS.glsl");
  raceProgram.addShader(GL_FRAGMENT_SHADER, "shaders/SimpleFS.glsl");

  //Pour la skybox
  skyboxProgram.addShader(GL_VERTEX_SHADER, "shaders/Skybox.vs.glsl");
  skyboxProgram.addShader(GL_FRAGMENT_SHADER, "shaders/Skybox.fs.glsl");
}

World3D::~World3D()
{
  //Utiliser un iterator declenche un bug hyper chelou (tente de detruire un deuxieme
  //pointeur vers la classe mere...)
  for (size_t i = 0; i < objects3D.size(); ++i)
  {
    delete objects3D[i];
  }

  objects3D.erase(objects3D.begin(), objects3D.end());
  delete camera;
  delete sun;

}

void World3D::init()
{
  std::string logInfo;
  if (!raceProgram.compileAndLinkShaders(logInfo))
  {
    throw std::runtime_error(logInfo);
  }
  logInfo.clear();

  if (!skyboxProgram.compileAndLinkShaders(logInfo))
  {
    throw std::runtime_error(logInfo);
  }

  /****** SKYBOX JOUR *****
  if(!skybox.init("textures/skybox/day","_deserted_back.tga","_deserted_front.tga","_deserted_up.tga","_deserted_bottom.tga","_deserted_right.tga","_deserted_left.tga"))
  {
    throw std::runtime_error("Impossible d'initialiser la SkyBox");
  }
  */

  /****** SKYBOX NUIT *****/
  if(!skybox.init("textures/skybox/night","nightsky_north.bmp","nightsky_south.bmp","nightsky_up.bmp","nightsky_down.bmp","nightsky_east.bmp","nightsky_west.bmp"))
  {
    throw std::runtime_error("Impossible d'initialiser la SkyBox");
  }
  
  skybox.setCamera(camera);
}

void World3D::draw() const
{
  //Mise a jour matrice ViewProjection
  //Attention : le vertex shader doit contenir les bonnes uniforms
  camera->updateViewProjectionMatrix();
  skyboxProgram.use();
  skybox.render(skyboxProgram);

  raceProgram.use();
  const glm::mat4& viewMatrix = camera->getViewMatrix();
  const glm::mat4& viewProjection = camera->getViewProjectionMatrix();
  GLint viewId = raceProgram.getUniformIndex("uView");
  GLint viewProjectionId = raceProgram.getUniformIndex("viewProjection");
  raceProgram.setUniform(viewId, viewMatrix);
  raceProgram.setUniform(viewProjectionId, viewProjection);

  //Ranger aussi la gestion des lumieres
  //Gestion des lumières ponctuelles
  /*GLuint m_lightsUBO;
  glGenBuffers(1,&m_lightsUBO);
  glBindBuffer(GL_UNIFORM_BUFFER, m_lightsUBO);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLight)* lights.size(), (const GLvoid*) lights[0], GL_DYNAMIC_DRAW);
  glBindBufferRange(GL_UNIFORM_BUFFER, 1, m_lightsUBO, 0, sizeof(PointLight)* lights.size()); */

  int i =0;
  for (auto oneLight = lights.begin(); oneLight != lights.end(); ++oneLight)
  {
    (*oneLight)->updateLight(viewMatrix);
    const glm::vec4& position = (*oneLight)->getLightPosition();
    const glm::vec3& intensity = (*oneLight)->getLightIntensity();
    GLint lightPosId = raceProgram.getUniformIndex("point.uLightPos");
    GLint lightIntensityId = raceProgram.getUniformIndex("point.uLi");
    raceProgram.setUniform(lightPosId,position);
    raceProgram.setUniform(lightIntensityId, intensity);
    ++i;
  }
  /*glBindBuffer(GL_UNIFORM_BUFFER,m_lightsUBO);
  glBufferSubData(GL_UNIFORM_BUFFER,0,lights.size(),lights.data());
  glBindBuffer(GL_UNIFORM_BUFFER,0);*/
  GLint nbLightsId = raceProgram.getUniformIndex("nbLights");
  raceProgram.setUniform(nbLightsId,i);

  //Gestion d'une spotLight
  spot->updateLightPosition();
  //spot->updateLightDirection();
  //spot->updateLight(viewMatrix);
  const glm::vec4& spotPos = spot->getLightPosition();
  const glm::vec4& spotDir = spot->getLightDirection();
  const glm::vec3& spotIntensity = spot->getLightIntensity();
  const float& spotCutoff = spot->getLightCutoff();
  GLint spotPosId = raceProgram.getUniformIndex("spot.uLightPos");
  GLint spotDirId = raceProgram.getUniformIndex("spot.uLightDir");
  GLint spotIntensityId = raceProgram.getUniformIndex("spot.uLi");
  GLint spotCutId = raceProgram.getUniformIndex("spot.uCutoff");
  raceProgram.setUniform(spotPosId,spotPos);
  raceProgram.setUniform(spotDirId,spotDir);
  raceProgram.setUniform(spotIntensityId, spotIntensity);
  raceProgram.setUniform(spotCutId,spotCutoff);

  //Gestion de la lumière directionnelle
  sun->updateLight(viewMatrix);
  const glm::vec4& direction = sun->getLightDirection();
  const glm::vec3& intensity = sun->getLightIntensity();
  GLint lightDirId = raceProgram.getUniformIndex("directional.uLightDir");
  GLint lightIntensityId = raceProgram.getUniformIndex("directional.uLi");
  raceProgram.setUniform(lightDirId,direction);
  raceProgram.setUniform(lightIntensityId, intensity);

  const glm::vec4& ambient = getAmbientLight();
  GLint ambientLightId = raceProgram.getUniformIndex("uAmbientLight");
  raceProgram.setUniform(ambientLightId, ambient);

  for (auto object3D = objects3D.begin(); object3D != objects3D.end(); ++object3D)
  {
    (*object3D)->setViewMatrix(camera->getViewMatrix());
    (*object3D)->update();
    (*object3D)->draw(raceProgram);
  }
}

void World3D::setCamera(Camera* newCamera)
{
  delete camera;
  camera = newCamera;
  skybox.setCamera(camera);
}

void World3D::setSpot(SpotLight* newSpot)
{
  delete spot;
  spot = newSpot;
}

void World3D::switchInBackwardView(){
  camera->switchInBackwardView();
}

void World3D::switchInForwardView(){
  camera->switchInForwardView();
}

void World3D::switchInLeftBendView(){
  camera->switchInLeftBendView();
}

void World3D::switchInRightBendView(){
  camera->switchInRightBendView();
}


void World3D::setSize(const unsigned int width, const unsigned int height){
  camera->setSize(width, height);
}
