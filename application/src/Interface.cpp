#include "Interface.hpp"
#include "Object2D.hpp"
#include "ObjectTexte.hpp"
#include <stdexcept>

Interface::Interface()
{
  object2DProgram.addShader(GL_VERTEX_SHADER, "shaders/tex2D.vs.glsl");
  object2DProgram.addShader(GL_FRAGMENT_SHADER, "shaders/tex2D.fs.glsl");

  objectTextProgram.addShader(GL_VERTEX_SHADER, "shaders/texte2D.vs.glsl");
  objectTextProgram.addShader(GL_FRAGMENT_SHADER, "shaders/texte2D.fs.glsl");
}

Interface::~Interface()
{
  for (size_t i = 0; i < objects2D.size(); ++i)
  {
    delete objects2D[i];
  }

  for (size_t i = 0; i < objectsTexte.size(); ++i)
  {
    delete objectsTexte[i];
  }

  objectsTexte.erase(objectsTexte.begin(), objectsTexte.end());
  objects2D.erase(objects2D.begin(), objects2D.end());
}

void Interface::init()
{
  std::string logInfo;
  if (!object2DProgram.compileAndLinkShaders(logInfo))
  {
    throw std::runtime_error(logInfo);
  }

  logInfo.clear();
  if (!objectTextProgram.compileAndLinkShaders(logInfo))
  {
    throw std::runtime_error(logInfo);
  }
}

void Interface::draw() const
{
  //Dessin des objets 2D
  object2DProgram.use();
  for(auto object2D = objects2D.begin(); object2D != objects2D.end(); ++object2D)
  {
    (*object2D)->update();
    (*object2D)->draw(object2DProgram);
  }

  //Dessin des objets Texte
  objectTextProgram.use();
  for (auto objectText = objectsTexte.begin(); objectText != objectsTexte.end(); ++objectText)
  {
    //ULTRA DEGUEU, trouver quand positionner les ObjectText, actuellement c'est un peu la fete du slip
    (*objectText)->update(10, 570, 20);
    (*objectText)->draw(objectTextProgram);
  }
}
