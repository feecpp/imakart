#include "SpotLight.hpp"
#include "Positionable.hpp"
#include <iostream>
#include <glm/gtx/quaternion.hpp>

SpotLight::SpotLight()
    :position(0.f,3.f,-3.f,1.f),direction(0.f,0.f,-3.f,0.f),intensity(5.5f,5.5f,5.5f), cutoff(0.f), objectToFollow(nullptr)
{
}

const glm::vec4 SpotLight::getLightPosition() const{
  return position;
}

const glm::vec4 SpotLight::getLightDirection() const{
  return direction;
}

const glm::vec3 SpotLight::getLightIntensity() const {
  return intensity;
}

const float SpotLight::getLightCutoff() const {
    return cutoff;
}

void SpotLight::updateLightPosition(){
    glm::vec3 initialDirection = glm::vec3(0.f, 0.f, -3.f);
    if (objectToFollow != nullptr) {
      direction = glm::vec4(glm::toMat3(objectToFollow->getOrientation()) * initialDirection,1.0f);
      position = glm::vec4(objectToFollow->getPosition(),1.0f)  - direction + glm::vec4(0.f,0.f,-5.f,1.f);
    }
}

void SpotLight::updateLightDirection(){
    //direction = dir + glm::vec3(0.f,-1.6f,0.f);
    direction = position + glm::vec4(30.f,0.f,30.f,-1.f);;
}

void SpotLight::updateLight(const glm::mat4 viewMatrix) {
    position = viewMatrix * position;
    direction = viewMatrix * direction;
}
