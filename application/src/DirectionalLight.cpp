#include "DirectionalLight.hpp"
#include "Positionable.hpp"

DirectionalLight::DirectionalLight()
  :direction(3.f,30.f,3.f),intensity(1.5f,1.5f,1.5f)
{
}

DirectionalLight::DirectionalLight(glm::vec3 direction)
    :direction(direction),intensity(1.5f,1.5f,1.5f)
{
}

const glm::vec3 DirectionalLight::getLightDirection() const {
  return direction;
}

const glm::vec3 DirectionalLight::getLightIntensity() const {
  return intensity;
}

void DirectionalLight::updateLight(const glm::mat4 viewMatrix){
    direction = glm::vec3(viewMatrix * glm::vec4(3.f,30.f,3.f, 0.f));
}
