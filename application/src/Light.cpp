#include "Light.hpp"

Light::Light()
  :direction(3.f,3.f,3.f),position(1.f,1.f,1.f),intensity(1.f,1.f,1.f)
{
}

const glm::vec3 Light::getLighDirection() const {
  return direction;
}

const glm::vec3 Light::getLightPosition() const{
  return position;
}

const glm::vec3 Light::getLightIntensity() const {
  return intensity;
}

void Light::updateLightDirection(const glm::mat4 viewMatrix) {
    direction = glm::vec3(viewMatrix * glm::vec4(3,3,3, 1));
    position = glm::vec3(viewMatrix * glm::vec4(1,1,1,1));
}
