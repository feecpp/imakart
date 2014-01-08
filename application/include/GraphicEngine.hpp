#ifndef GRAPHICENGINE_HPP
#define GRAPHICENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ShaderProgram.hpp"
#include <map>
#include "Observable.hpp"
#include "World3D.hpp"
#include "MotionBlur.hpp"

class Interface;
class Camera;
class Light;

/**
 * @brief Les options graphiques bas niveau
 * (pas forcÃ©ment la meilleure maniÃ¨re de faire)
 */
struct GraphicSettings
{
  GraphicSettings()
    : FPS(30), WINDOW_WIDTH(1024), WINDOW_HEIGHT(768), WINDOW_BPP(32)
  {
    FRAME_DURATION = 1000.f / FPS;
  }
  
  unsigned int FPS;
  unsigned int FRAME_DURATION;
  unsigned int WINDOW_WIDTH;
  unsigned int WINDOW_HEIGHT;
  unsigned int WINDOW_BPP;
};

/**
 * @brief The GraphicEngine class
 * Contient une liste d'objet 3D Ã  afficher.
 * Contient Ã©galement une liste d'objets 2D
 * qui constituent l'interface.
 */
class GraphicEngine
{
public:
  GraphicEngine();
  ~GraphicEngine();

  sf::RenderWindow& init();
  void renderFrame();
  void swapBuffers();

  const GraphicSettings& getSettings() const;

  void setNewSizeWindow(const unsigned int width, const unsigned int height);

  /** Delete le world3D actuel et prend le nouveau.
   * Prend en charge la memoire du nouveau.
   * Appelle la methode init() de l'interface
   */
  void setCurrentWorld3D(World3D* newWorld3D);

  /** Delete le world3D actuel et prend le nouveau.
   * Prend en charge la memoire du nouveau.
   * Appel la methode init() de l'interface
   */
  void setCurrentInterface(Interface* newInterface);

  Interface& getCurrentInterface()
    {assert(interface); return *interface;}

  GLuint getTextureFromTabTexture(const unsigned int positionToSelect)
    { return tabTextures[positionToSelect]; }

  World3D& getWorld3D()
    {assert(world3D); return *world3D;}
  
  sf::RenderWindow& getWindow();

  void setMotionBlur(bool enable)
    {motionBlurEnabled = enable; motionBlur->reinit();}

  void reset();

private:
  void initTextures();

  GraphicSettings settings;

  World3D* world3D;
  Interface* interface;

  //Light* currentLight;

  MotionBlur* motionBlur;
  bool motionBlurEnabled;

  sf::RenderWindow window;
  std::vector<GLuint> tabTextures;



};

#endif // GRAPHICENGINE_HPP
