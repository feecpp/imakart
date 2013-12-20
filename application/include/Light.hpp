#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

class Positionable;

class Light {
public:
    Light();
    Light(glm::vec3 direction); // Constructeur pour une lumière directionnelle avec args
    Light(glm::vec3 position, glm::vec3 intensity); // Constructeur pour une lumière ponctuelle avec args


    const glm::vec3 getLighDirection() const;
    const glm::vec3 getLightPosition() const;
    const glm::vec3 getLightIntensity() const;
    void updateLightDirection();
    void updateLight(const glm::mat4 viewMatrix);

    void linkToPositionable(const Positionable& objectToFollow)
      {this->objectToFollow = &objectToFollow;}

private:
  const Positionable* objectToFollow;
  glm::vec3 direction;
  glm::vec3 position;
  glm::vec3 intensity;
};

#endif // LIGHT_HPP
