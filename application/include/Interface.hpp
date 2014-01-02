#ifndef IMAKART_INTERFACE_HPP
#define IMAKART_INTERFACE_HPP

#include <vector>
#include "ShaderProgram.hpp"
#include "TimeLimitedText.hpp"

class Object2D;
class ObjectTexte;

class Interface
{
public:
  Interface();

  ~Interface();

  void init();
  void update();

  void draw() const;

  void addObject2D(Object2D* newObject2D)
    {objects2D.push_back(newObject2D);}

  void addObjectTexte(ObjectTexte* newObjectTexte)
    {objectsTexte.push_back(newObjectTexte);}

  void addTimeLimitedText(TimeLimitedText* newTimeLimitedText)
    {newTimeLimitedText->start(); timeLimitedTexts.push_back(newTimeLimitedText);}

private:
  std::vector<Object2D* > objects2D;
  std::vector<ObjectTexte* > objectsTexte;
  std::vector<TimeLimitedText* > timeLimitedTexts;

  glimac::ShaderProgram object2DProgram;
  glimac::ShaderProgram objectTextProgram;

};

#endif // IMAKART_INTERFACE_HPP
