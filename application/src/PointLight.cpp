#include "PointLight.hpp"

PointLight::PointLight()
  :position(1.f,1.f,1.f),intensity(1.5f,1.5f,1.5f)
{
}

PointLight::PointLight(glm::vec3 position, glm::vec3 intensity)
    :position(position),intensity(intensity)
{
}

const glm::vec3 PointLight::getLightPosition() const{
  return position;
}

const glm::vec3 PointLight::getLightIntensity() const {
  return intensity;
}

void PointLight::updateLight(const glm::mat4 viewMatrix) {
    position = glm::vec3(viewMatrix * glm::vec4(1,1,1,1));
}

