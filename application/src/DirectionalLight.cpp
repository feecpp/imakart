#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight()
  :direction(-50.f,100.f,-100.f,0.f),info(-50.f,100.f,-100.f,0.f),intensity(0.1f,0.1f,0.5f)
{
}

DirectionalLight::DirectionalLight(glm::vec4 direction)
    :direction(direction),info(direction),intensity(1.5f,1.5f,1.5f)
{
}

DirectionalLight::DirectionalLight(glm::vec3 intensity)
    :direction(-50.f,100.f,-100.f,0.f),info(-50.f,100.f,-100.f,0.f),intensity(intensity)
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

void DirectionalLight::setLightIntensity(glm::vec3 intensity_){
    intensity = intensity_;
}

void DirectionalLight::updateLight(const glm::mat4 viewMatrix){
    direction = viewMatrix * info;
}
