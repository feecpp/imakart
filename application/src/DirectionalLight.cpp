#include "DirectionalLight.hpp"
#include "Positionable.hpp"

DirectionalLight::DirectionalLight()
  :direction(3.f,30.f,3.f,0.f),intensity(0.5f,0.5f,0.5f)
{
}

DirectionalLight::DirectionalLight(glm::vec4 direction)
    :direction(direction),intensity(2.5f,2.5f,2.5f)
{
}

const glm::vec4 DirectionalLight::getLightDirection() const {
  return direction;
}

const glm::vec3 DirectionalLight::getLightIntensity() const {
  return intensity;
}

void DirectionalLight::updateLight(const glm::mat4 viewMatrix){
    direction = viewMatrix * glm::vec4(3.f,30.f,3.f, 0.f);
}
