#ifndef GRAPHICENGINE_HPP
#define GRAPHICENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ShaderProgram.hpp"
#include <map>
#include <Texte2D.hpp>


class Object3D;
class Object2D;
class Camera;
class Light;
class Skybox;

/**
 * @brief Les options graphiques bas niveau
 * (pas forcément la meilleure manière de faire)
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
 * Contient une liste d'objet 3D �  afficher.
 * Contient également une liste d'objets 2D
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

  /**
   * @brief reset
   * Nettoie la liste des objets 2D et 3D.
   */
  void reset();

  /**
   * @brief addObject3D Ajout un objet 3D dans la liste d'affichage
   * du GraphicEngine. Le GraphicEngine devient propriÃ©taire de cet objet
   * et prend en charge sa destruction. Actuellement dÃ©finir une camÃ©ra dÃ©fini
   * l'Ã©ventuelle ancienne camÃ©ra dÃ©tenue par le GraphicEngine.
   * @param newObject3D
   */
  void addObject3D(Object3D* newObject3D)
    {objects3D.push_back(newObject3D);}
    
  void addObject2D(Object2D* newObject2D)
    {objects2D.push_back(newObject2D);}

  /**
   * @brief setCamera défini une nouvelle caméra
   * pour afficher la scène. Le GraphicEngine devient le propriÃ©taire
   * de newCamera et prendra en charge sa destruction.
   * @param newCamera
   */
  void setCamera(Camera* newCamera);

  /*
   *setLight d�fini une nouvelle source de lumi�re
   */
  void setLight(Light* newLight);


  /*
   * C'est un peu moisi comme méthode
   * mais ça suffit pour l'instant. A améliorier
   * quand le graphique engine aura plus de ShaderProgram
   * �  gérer
   **/
  void useMenuProgram();
  void useRaceProgram();
  void useTexteProgram();
  void useSkyboxProgram();

  GLuint getTextureFromTabTexture(const unsigned int positionToSelect)
    { return tabTextures[positionToSelect]; }

  Texte2D* chrono;

private:
  void drawWorld();
  void drawInterface();
  void initShaderPrograms();
  void initTextures();

  GraphicSettings settings;

  Camera* currentCamera;

  Light* currentLight;
  Skybox* skybox;

  //Avant de trouver une meilleure mÃ©thode...
  glimac::ShaderProgram* currentProgram;
  glimac::ShaderProgram* menuProgram;
  glimac::ShaderProgram* raceProgram;
  glimac::ShaderProgram* texte2DProgram;
  glimac::ShaderProgram* skyboxProgram;

  //GraphicSettings settings;
  std::vector<Object3D* > objects3D;
  std::vector<Object2D* > objects2D;

  sf::RenderWindow window;
  sf::Font font;
  std::vector<GLuint> tabTextures;

};

#endif // GRAPHICENGINE_HPP
