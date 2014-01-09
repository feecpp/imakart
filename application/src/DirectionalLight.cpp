#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight()
  :direction(-10.f,300.f,-100.f,0.f),info(-10.f,300.f,-100.f,0.f),intensity(1.5f,1.5f,1.5f)
{
}

DirectionalLight::DirectionalLight(glm::vec4 direction)
    :direction(direction),info(direction),intensity(1.5f,1.5f,1.5f)
{
}

DirectionalLight::DirectionalLight(glm::vec4 direction, glm::vec3 intensity)
    :direction(direction),info(direction),intensity(intensity)
{
}

const glm::vec4 DirectionalLight::getLightDirection() const {
  return direction;
}

const glm::vec3 DirectionalLight::getLightIntensity() const {
  return intensity;
}

void DirectionalLight::updateLight(const glm::mat4 viewMatrix){
    direction = viewMatrix * info;
}
