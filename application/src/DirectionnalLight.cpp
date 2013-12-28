#include "DirectionnalLight.hpp"
#include "Positionable.hpp"

DirectionnalLight::DirectionnalLight()
  :direction(3.f,30.f,3.f),intensity(1.5f,1.5f,1.5f)
{
}

DirectionnalLight::DirectionnalLight(glm::vec3 direction)
    :direction(direction),intensity(1.5f,1.5f,1.5f)
{
}

const glm::vec3 DirectionnalLight::getLightDirection() const {
  return direction;
}

const glm::vec3 DirectionnalLight::getLightIntensity() const {
  return intensity;
}

void DirectionnalLight::updateLight(const glm::mat4 viewMatrix){
    direction = glm::vec3(viewMatrix * glm::vec4(3,30,3, 1));
}
