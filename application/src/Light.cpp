#include "Light.hpp"

Light::Light()
  :direction(0.f,0.f,0.f), intensity(1.f,1.f,1.f)
{
}

const glm::vec3 Light::getLighDirection() const {
  return direction;
}

const glm::vec3 Light::getLightIntensity() const {
  return intensity;
}

void Light::updateLight(const glm::mat4 viewMatrix) {
    direction = glm::vec3(viewMatrix * glm::vec4(3, 3, 3, 1)); //A MODIFIER
}
