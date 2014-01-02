#include "SpotLight.hpp"

SpotLight::SpotLight()
    :position(1.f,30.f,1.f),direction(3.f,3.f,3.f),intensity(3.5f,3.5f,3.5f), cutoff(0.f)
{
}

const glm::vec3 SpotLight::getLightPosition() const{
  return position;
}

const glm::vec3 SpotLight::getLightDirection() const{
  return direction;
}

const glm::vec3 SpotLight::getLightIntensity() const {
  return intensity;
}

const float SpotLight::getLightCutoff() const {
    return cutoff;
}

void SpotLight::updateLightPosition(const glm::vec3 pos){
    position = pos + glm::vec3(10.f,-1.6f,0.f);
}

void SpotLight::updateLightDirection(const glm::vec3 dir){
    //direction = dir + glm::vec3(0.f,-1.6f,0.f);
    direction = position + glm::vec3(30.f,0.f,30.f);;
}

void SpotLight::updateLight(const glm::mat4 viewMatrix) {
    //position = glm::vec3(viewMatrix * glm::vec4(position,1.f));
    direction = glm::vec3(viewMatrix * glm::vec4(3.f,3.f,3.f,1.f));
}
