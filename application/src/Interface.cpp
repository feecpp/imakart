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

  for (size_t i = 0; i < timeLimitedTexts.size(); ++i)
  {
    delete timeLimitedTexts[i];
  }

  objectsTexte.erase(objectsTexte.begin(), objectsTexte.end());
  objects2D.erase(objects2D.begin(), objects2D.end());
  timeLimitedTexts.erase(timeLimitedTexts.begin(), timeLimitedTexts.end());
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

void Interface::update()
{
  for (auto timeLimitedText = timeLimitedTexts.begin(); timeLimitedText != timeLimitedTexts.end(); ++timeLimitedText)
  {
    (*timeLimitedText)->update();
    if ((*timeLimitedText)->isFinished())
    {
      delete *timeLimitedText;
      *timeLimitedText = nullptr;
      timeLimitedTexts.erase(timeLimitedText);
      timeLimitedText = timeLimitedTexts.begin();
      if (timeLimitedText == timeLimitedTexts.end())
        break;
    }
  }
}

void Interface::draw() const
{

  //Dessin des objets Texte
  objectTextProgram.use();
  for (auto objectText = objectsTexte.begin(); objectText != objectsTexte.end(); ++objectText)
  {
    // Dessiner le text avnt les objets 2D permet de les voir dans les menus sinon ils sont cachés sous les menus !
    // Côté logique, c'est pas ce que j'avais en tête mais ça fonctionne
    (*objectText)->update();
    (*objectText)->draw(objectTextProgram);
  }

  for (auto timeLimitedText = timeLimitedTexts.begin(); timeLimitedText != timeLimitedTexts.end(); ++timeLimitedText)
  {
    (*timeLimitedText)->draw(objectTextProgram);
  }

  //Dessin des objets 2D
  object2DProgram.use();
  for(auto object2D = objects2D.begin(); object2D != objects2D.end(); ++object2D)
  {
    (*object2D)->update();
    (*object2D)->draw(object2DProgram);
  }


}
