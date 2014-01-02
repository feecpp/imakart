#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include <glm/glm.hpp>


class SpotLight
{
public:
    SpotLight();
    SpotLight(glm::vec3 position);
    SpotLight(glm::vec3 position, glm::vec3 intensity);

    const glm::vec3 getLightPosition() const;
    const glm::vec3 getLightDirection() const;
    const glm::vec3 getLightIntensity() const;
    const float getLightCutoff() const;
    void updateLightPosition(const glm::vec3 pos);
    void updateLightDirection(const glm::vec3 dir);
    void updateLight(const glm::mat4 viewMatrix);

private:
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 intensity;
  float cutoff;
};

#endif // POSLIGHT_HPP
