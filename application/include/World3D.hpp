#ifndef WORLD3D_HPP
#define WORLD3D_HPP

#include <vector>
#include <ShaderProgram.hpp>
#include "Skybox.hpp"

class Object3D;

class World3D
{
public:
  World3D();

  ~World3D();

  void init();

  void draw() const;

  /**
   * @brief addObject3D Ajout un objet 3D dans la liste d'affichage
   * du GraphicEngine. Le GraphicEngine devient proprietaire de cet objet
   * et prend en charge sa destruction. Actuellement definir une camera defini
   * l'eventuelle ancienne camera detenue par le GraphicEngine.
   * @param newObject3D
   */
  void addObject3D(Object3D* newObject3D)
    {objects3D.push_back(newObject3D);}


private:
  std::vector<Object3D* > objects3D;
  glimac::ShaderProgram raceProgram;
  glimac::ShaderProgram skyboxProgram;

  Skybox skybox;
};

#endif // WORLD3D_HPP
