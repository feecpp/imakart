#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include <glm/glm.hpp>
#include <iostream>

class Positionable;

class SpotLight
{
public:
    SpotLight();
    SpotLight(glm::vec4 position);
    SpotLight(glm::vec4 position, glm::vec3 intensity);

    const glm::vec4 getLightPosition() const;
    const glm::vec4 getLightDirection() const;
    const glm::vec3 getLightIntensity() const;
    const float getLightCutoff() const;
    void updateLightPosition();
    void updateLightDirection();
    void updateLight(const glm::mat4 viewMatrix);

    void linkToPositionable(const Positionable& object)
    {this->objectToFollow = &object; std::cout<<"objectToFollow change :"<<std::endl;}

private:
  const Positionable* objectToFollow;
  glm::vec4 position;
  glm::vec4 direction;
  glm::vec3 intensity;
  float cutoff;
};

#endif // POSLIGHT_HPP
