#ifndef GRAPHICENGINE_HPP
#define GRAPHICENGINE_HPP

#include <SDL/SDL.h>
#include <vector>

class Object3D;

/**
 * @brief Les options graphiques bas niveau
 */
struct GraphicSettings
{
  Uint32 FPS = 30;
  Uint32 FRAME_DURATION = 1000.f / FPS;

  Uint32 WINDOW_WIDTH = 800;
  Uint32 WINDOW_HEIGHT = 600;
  Uint32 WINDOW_BPP = 32;
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
  void renderFrame();
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
