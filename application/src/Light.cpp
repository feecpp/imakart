#include "Light.hpp"

Light::Light()
  :direction(0.f,0.f,-5.f), intensity(0.f,0.f,0.f)
{
}

const glm::vec3 Light::getLighDirection() const {
  return direction;
}

const glm::vec3 Light::getLightIntensity() const {
  return intensity;
}
