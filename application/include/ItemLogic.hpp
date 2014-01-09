#ifndef ITEMLOGIC_HPP
#define ITEMLOGIC_HPP

#include "Positionable.hpp"
#include "BoundingBox.hpp"
#include <string>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ItemInterface;

class ItemLogic: public Positionable{
public:
  ItemLogic(const std::string oName);
  ItemLogic(const ItemLogic& other);
  ~ItemLogic();

  const glm::vec3 getDirection() const
    {return glm::normalize(glm::toMat3(orientation) * glm::vec3(0,0,-1)); }

  const glm::vec3& getPosition() const
  	{return position;}

  const glm::quat& getOrientation() const
  	{return orientation;}

  const BoundingBox& getBoundingBox() const
    {return boundingBox;}

  virtual const bool isVisible() const
    {return visible;}

  void setNotVisible()
    {visible = false;}

  void noInterface();
  void update();
  void launch(const glm::vec3 positionLauncher, const glm::quat orientationLauncher, const float directionAngleLauncher);
  void updateLaunch();
  void colision();

  const std::string getEffect();
  const std::string& getName();

private:
  BoundingBox boundingBox;

  glm::vec3 position;
  glm::quat orientation;
  float directionAngle;

  std::string name;
  std::string effect;
  bool used;

  bool colid;
  float timeBeforeOtherColid;

  bool visible;
  float lifeTime;
  
  ItemInterface* myInterface;
};

#endif