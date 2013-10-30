#ifndef GRAPHICENGINE_HPP
#define GRAPHICENGINE_HPP

#include <SDL/SDL.h>
#include <vector>
#include <string>
#include "ShaderProgram.hpp"
#include <map>


class Object3D;
class Object2D;

/**
 * @brief Les options graphiques bas niveau
 * (pas forcément la meilleure manière de faire)
 */
struct GraphicSettings
{
  GraphicSettings()
    : FPS(30), WINDOW_WIDTH(800), WINDOW_HEIGHT(600), WINDOW_BPP(32)
  {
    FRAME_DURATION = 1000.f / FPS;
  }
  
  Uint32 FPS;
  Uint32 FRAME_DURATION;
  Uint32 WINDOW_WIDTH;
  Uint32 WINDOW_HEIGHT;
  Uint32 WINDOW_BPP;
};

/**
 * @brief The GraphicEngine class
 * Contient une liste d'objet 3D à afficher.
 * Contient également une liste d'objets 2D
 * qui constituent l'interface.
 */
class GraphicEngine
{
public:
  ~GraphicEngine();
  //TODO
  bool init();
  void renderFrame();
  void swapBuffers();

  /**
   * @brief addObject3D Ajout un objet 3D dans la liste d'affichage
   * du GraphicEngine. Le GraphicEngine devient propriétaire de cet objet
   * et prend en charge sa destruction.
   * @param newObject3D
   */
  void addObject3D(Object3D* newObject3D)
    {objects3D.push_back(newObject3D);}
    
  void addObject2D(Object2D* newObject2D)
    {objects2D.push_back(newObject2D);}

private:
  void drawWorld();
  void drawInterface();
  void initShaderPrograms();

  glimac::ShaderProgram* menuProgram;
  glimac::ShaderProgram* raceProgram;

  GraphicSettings settings;
  std::vector<Object3D* > objects3D;
  std::vector<Object2D* > objects2D;

};

#endif // GRAPHICENGINE_HPP
