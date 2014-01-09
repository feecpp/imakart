#include "BoundingBox.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_major_storage.hpp>

std::map<CollisionModel3D*, unsigned int> BoundingBox::memoryMap;

BoundingBox::BoundingBox(const BoundingBox& other)
  : collisionModel(other.collisionModel), position(other.position), size(other.size), orientation(other.orientation)
{
  updateModelMatrix();
}

BoundingBox::BoundingBox(glm::vec3 position, glm::vec3 size)
  : position(position), size(size)
{
  float v1[3], v2[3], v3[3], v4[3], v5[3], v6[3], v7[3], v8[3];
  v1[0] = -0.5 * size.x; v1[1] = -0.5 * size.y, v1[2] = +0.5 * size.z;
  v2[0] = -0.5 * size.x; v2[1] = +0.5 * size.y, v2[2] = +0.5 * size.z;
  v3[0] = +0.5 * size.x; v3[1] = +0.5 * size.y, v3[2] = +0.5 * size.z;
  v4[0] = +0.5 * size.x; v4[1] = -0.5 * size.y, v4[2] = +0.5 * size.z;
  v5[0] = -0.5 * size.x; v5[1] = -0.5 * size.y, v5[2] = -0.5 * size.z;
  v6[0] = -0.5 * size.x; v6[1] = +0.5 * size.y, v6[2] = -0.5 * size.z;
  v7[0] = +0.5 * size.x; v7[1] = +0.5 * size.y, v7[2] = -0.5 * size.z;
  v8[0] = +0.5 * size.x; v8[1] = -0.5 * size.y, v8[2] = -0.5 * size.z;


  collisionModel = newCollisionModel3D();
  memoryMap.insert(std::pair<CollisionModel3D* , unsigned int>(collisionModel, 1));

  //Face avant
  collisionModel->addTriangle(v1, v2, v3);
  collisionModel->addTriangle(v2, v3, v4);
  //Face arrière
  collisionModel->addTriangle(v5, v6, v7);
  collisionModel->addTriangle(v7, v8, v5);
  //Face haut
  collisionModel->addTriangle(v2, v6, v3);
  collisionModel->addTriangle(v6, v7, v3);
  //Face bas
  collisionModel->addTriangle(v1, v5, v4);
  collisionModel->addTriangle(v5, v8, v4);
  //Face gauche
  collisionModel->addTriangle(v1, v2, v5);
  collisionModel->addTriangle(v2, v6, v5);
  //Face droite
  collisionModel->addTriangle(v4, v3, v8);
  collisionModel->addTriangle(v3, v7, v8);

  collisionModel->finalize();

  updateModelMatrix();
}

BoundingBox::~BoundingBox()
{
  memoryMap[collisionModel]--;
  if (memoryMap[collisionModel] == 0)
  {
    delete collisionModel;
    memoryMap.erase(collisionModel);
  }
}

bool BoundingBox::collideWith(const BoundingBox& other) const
{
  bool result = collisionModel->collision(other.collisionModel);
  assert(!result);
}

void BoundingBox::updateModelMatrix()
{
  modelMatrix = glm::mat4(1.f);
  //modelMatrix = glm::toMat4(orientation) * modelMatrix;
  modelMatrix = glm::translate(glm::mat4(1.f), position) * modelMatrix;
  rowMajorModelMatrix = glm::rowMajor4(modelMatrix);

  collisionModel->setTransform(glm::value_ptr(modelMatrix));
}

const glm::quat& BoundingBox::getOrientation() const
{
  return orientation;
}
