#include "PointLight.hpp"

PointLight::PointLight()
  :position(1.f,30.f,1.f),info(1.f,30.f,1.f),intensity(3.5f,3.5f,3.5f)
{
}

PointLight::PointLight(glm::vec3 position)
    :position(position),info(position),intensity(3.5f,3.5f,3.5f)
{
}

PointLight::PointLight(glm::vec3 position, glm::vec3 intensity)
    :position(position),info(position),intensity(intensity)
{
}

const glm::vec3 PointLight::getLightPosition() const{
  return position;
}

const glm::vec3 PointLight::getLightIntensity() const {
  return intensity;
}

void PointLight::updateLight(const glm::mat4 viewMatrix) {
    position = glm::vec3(viewMatrix * glm::vec4(info,1.f));
}
