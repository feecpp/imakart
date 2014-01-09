#include "ItemLogic.hpp"
#include "ObjectFile.hpp"
#include "ItemInterface.hpp"
#include <iostream>
#include <cassert>

ItemLogic::ItemLogic(const std::string oName):
	boundingBox(glm::vec3(0), glm::vec3(2)), position(glm::vec3(0)), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))), directionAngle(0), name(oName), used(false), colid(false), timeBeforeOtherColid(0), visible(true), lifeTime(300), myInterface(ItemInterface::getSingletonItemInterface())
{
  const std::string path = "items/"+name+".item";
  //Je crée un ObjectFile à partir du fichier.item et récupère un std::map
  ObjectFile itemFile(path);
  std::map<std::string, std::string> map = itemFile.getData();

  name = map["Name"];
  effect = map["Effect"] ;
}

ItemLogic::ItemLogic(const ItemLogic& other):
  boundingBox(other.boundingBox), position(other.position), orientation(other.orientation), directionAngle(other.directionAngle), name(other.name), effect(other.effect), used(other.used), colid(other.colid), timeBeforeOtherColid(other.timeBeforeOtherColid), visible(true), lifeTime(300), myInterface(other.myInterface)
{}

ItemLogic::~ItemLogic(){}

const std::string ItemLogic::getEffect(){
	assert(used == false);
	used = true;

	return effect;
}

const std::string& ItemLogic::getName(){
  return name;
}

void ItemLogic::noInterface(){
  update();
  myInterface = nullptr;
}

void ItemLogic::update(){
  myInterface->noSelected();
  myInterface->setName(name);
}

void ItemLogic::launch(const glm::vec3 positionLauncher, const glm::quat orientationLauncher, const float directionAngleLauncher){
  position = positionLauncher;
  orientation = orientationLauncher;
  directionAngle = directionAngleLauncher;
  boundingBox.setPosition(position);
}

void ItemLogic::updateLaunch()
{
  position += getDirection();
  timeBeforeOtherColid -= 1;
  lifeTime -= 1;
  boundingBox.setPosition(position);

  if(lifeTime <= 0){
    visible = false;
  }
}

void ItemLogic::colision()
{
  if(!colid){
    colid = true;
    timeBeforeOtherColid = 10;
    directionAngle = -directionAngle;

    orientation = glm::angleAxis(directionAngle, glm::vec3(0.f, 1.f, 0.f));
  }

  if(timeBeforeOtherColid <= 0){
    colid = false;
  }
}