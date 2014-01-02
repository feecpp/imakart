#include "SpotLight.hpp"
#include "Positionable.hpp"
#include <iostream>
#include <glm/gtx/quaternion.hpp>

SpotLight::SpotLight()
    :position(0.f,3.f,-3.f),direction(0.f,0.f,-3.f),intensity(5.5f,5.5f,5.5f), cutoff(0.f), objectToFollow(nullptr)
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

void SpotLight::updateLightPosition(){
    glm::vec3 initialDirection = glm::vec3(0.f, -2.f, -3.f);
    if (objectToFollow != nullptr) {
      direction = glm::toMat3(objectToFollow->getOrientation()) * initialDirection;;
      position = objectToFollow->getPosition()  - direction + glm::vec3(0.f,0.f,-5.f);
    }else{
        std::cout << "Erreur : objectToFollow est vide" <<std::endl;
    }
}

void SpotLight::updateLightDirection(){
    //direction = dir + glm::vec3(0.f,-1.6f,0.f);
    direction = position + glm::vec3(30.f,0.f,30.f);;
}

void SpotLight::updateLight(const glm::mat4 viewMatrix) {
    position = glm::vec3(viewMatrix * glm::vec4(position,1.f));
    direction = glm::vec3(viewMatrix * glm::vec4(direction,1.f));
}
