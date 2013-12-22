#include "Light.hpp"
#include "Positionable.hpp"

Light::Light()
  :objectToFollow(nullptr),direction(3.f,30.f,3.f),position(1.f,1.f,1.f),intensity(1.5f,1.5f,1.5f)
{
}

Light::Light(glm::vec3 direction) // Constructeur pour lumière directionnelle
    :objectToFollow(nullptr),direction(direction),position(0.f,0.f,0.f),intensity(1.5f,1.5f,1.5f)
{
}

Light::Light(glm::vec3 position, glm::vec3 intensity) // Constructeur pour lumière ponctuelle
    :objectToFollow(nullptr),direction(0.f,0.f,0.f),position(position),intensity(intensity)
{
}

const glm::vec3 Light::getLighDirection() const {
  return direction;
}

const glm::vec3 Light::getLightPosition() const{
  return position;
}

const glm::vec3 Light::getLightIntensity() const {
  return intensity;
}

void Light::updateLightDirection(){
    //La lumière suit le Kart, un peu comme le soleil nous "suit"
    direction = objectToFollow->getPosition();

}

void Light::updateLight(const glm::mat4 viewMatrix) {
    direction = glm::vec3(viewMatrix * glm::vec4(3,30,3, 1));
    position = glm::vec3(viewMatrix * glm::vec4(1,1,1,1));
}
