#include "BoundingBox.hpp"
#include <glm/gtx/quaternion.hpp>

BoundingBox::BoundingBox()
  : position(0.f), size(1.f), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))), positionNearOrigin(0.5f), visible(true)
{

}

BoundingBox::BoundingBox(glm::vec3 position, glm::vec3 size)
  : position(position), size(size)
{
  positionNearOrigin = calculPositionNearOrigin();
}

//http://fr.openclassrooms.com/informatique/cours/theorie-des-collisions/aabb-3d
bool BoundingBox::collideWith(const BoundingBox& other) const
{
  if ((other.positionNearOrigin.x >= positionNearOrigin.x + size.x)      // trop à droite
      || (other.positionNearOrigin.x + other.size.x <= positionNearOrigin.x) // trop à gauche
      || (other.positionNearOrigin.y >= positionNearOrigin.y + size.y) // trop en bas
      || (other.positionNearOrigin.y + other.size.y <= positionNearOrigin.y)  // trop en haut
      || (other.positionNearOrigin.z >= positionNearOrigin.z + size.z)   // trop derrière
      || (other.positionNearOrigin.z + other.size.z <= positionNearOrigin.z))  // trop devant
  {
    return false;
  }
  else
  {
    return true;
  }
}

const glm::quat& BoundingBox::getOrientation() const
{
  return orientation;
}
