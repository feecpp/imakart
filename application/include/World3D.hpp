#ifndef WORLD3D_HPP
#define WORLD3D_HPP

#include <vector>
#include <glm/glm.hpp>
#include <ShaderProgram.hpp>
#include "Skybox.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Camera.hpp"

class Object3D;
class Light;


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

  /**
   * @brief setCamera dÃ©fini une nouvelle camÃ©ra
   * pour afficher la scÃ¨ne. Le GraphicEngine devient le propriÃƒÂ©taire
   * de newCamera et prendra en charge sa destruction.
   * @param newCamera
   */
  void setCamera(Camera* newCamera);

  /*
<<<<<<< HEAD
   * Change de la premiere personne à la troisieme personne
   */
  void switchView();

  /*
   *setLight défini une nouvelle source de lumière
=======
   *addLight permet d'avoir plusieurs lumières ponctuelles dans un vector
>>>>>>> 161359c8cc56e33a08055671b6faa9503cf810a9
   */
  void addLight(PointLight* newLight)
      {lights.push_back(newLight);}

  const glm::vec4 getAmbientLight() const
    {return ambientLight;}


private:
  std::vector<Object3D* > objects3D;
  glimac::ShaderProgram raceProgram;
  glimac::ShaderProgram skyboxProgram;

  std::vector<PointLight* > lights;
  Skybox skybox;
  Camera* camera;
  DirectionalLight* sun;
  glm::vec4 ambientLight;

};

#endif // WORLD3D_HPP
