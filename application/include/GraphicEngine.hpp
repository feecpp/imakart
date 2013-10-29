#ifndef GRAPHICENGINE_HPP
#define GRAPHICENGINE_HPP

#include <SDL/SDL.h>
#include <vector>
#include "GameEngine.hpp" 

class Object3D;

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
  //TODO
  bool init();
  void renderFrame(GameEngine* gameEngine);
  void swapBuffers();

  void addObject3D(Object3D* newObject3D)
    {objects3D.push_back(newObject3D);}

private:
  void drawWorld();
  void drawInterface();

  GraphicSettings settings;
  std::vector<Object3D* > objects3D;

};

#endif // GRAPHICENGINE_HPP
