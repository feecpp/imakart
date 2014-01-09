#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "Positionable.hpp" //Pour opuvoir la dessiner => debug
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "coldet.h"
#include <map>

/**
 * @brief The BoundingBox class
 * Premiere classe en rapport avec la physique.
 * BoundingBox pour test collisions type AABB.
 * /!\ Ici une BoundingBox est un parrallellepipede rectangle.
 */
class BoundingBox : public Positionable
{
public:
  BoundingBox(const BoundingBox& other);
  BoundingBox(glm::vec3 position, glm::vec3 size);
  ~BoundingBox();

  void setPosition(glm::vec3 newPosition)
  {
    position = newPosition;
    updateModelMatrix();
  }

  virtual const glm::vec3& getPosition() const
    {return position;}

  const glm::vec3& getSize() const
    {return size;}

  //http://fr.openclassrooms.com/informatique/cours/theorie-des-collisions/aabb-3d
  bool collideWith(const BoundingBox& other) const;

  virtual const glm::quat& getOrientation() const;

private:
  static std::map<CollisionModel3D*, unsigned int> memoryMap;

  void updateModelMatrix();
  CollisionModel3D* collisionModel;
  bool owner;

  ///La position de la BB est son centre
  glm::vec3 position;
  glm::vec3 size;
  glm::quat orientation;
  glm::mat4 modelMatrix;
  glm::mat4 rowMajorModelMatrix;
};

#endif // BOUNDINGBOX_HPP
