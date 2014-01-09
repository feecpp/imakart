#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "Positionable.hpp" //Pour opuvoir la dessiner => debug
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

/**
 * @brief The BoundingBox class
 * Premiere classe en rapport avec la physique.
 * BoundingBox pour test collisions type AABB.
 * /!\ Ici une BoundingBox est un parrallellepipede rectangle.
 */
class BoundingBox : public Positionable
{
public:

  BoundingBox();
  BoundingBox(glm::vec3 position, glm::vec3 size);

  void setPosition(glm::vec3 newPosition)
  {
    position = newPosition;
    positionNearOrigin = calculPositionNearOrigin();
  }

  virtual const glm::vec3& getPosition() const
    {return position;}

  void setSize(glm::vec3 newSize)
  {
    size = newSize;
    positionNearOrigin = calculPositionNearOrigin();
  }

  const glm::vec3& getSize() const
    {return size;}

  //http://fr.openclassrooms.com/informatique/cours/theorie-des-collisions/aabb-3d
  bool collideWith(const BoundingBox& other) const;

  virtual const glm::quat& getOrientation() const;

  virtual const bool isVisible() const
    {return visible;}

private:
  glm::vec3 calculPositionNearOrigin()
  {
    return glm::vec3(position.x - size.x / 2.f, position.y - size.y / 2.f, position.z - size.z / 2.f);
  }

  ///La position de la BB est son centre
  glm::vec3 position;
  glm::vec3 size;
  glm::quat orientation;

  //On utilise le point de la BB le plus proche de l'origine pour les calculs
  glm::vec3 positionNearOrigin;

  bool visible;
};

#endif // BOUNDINGBOX_HPP
