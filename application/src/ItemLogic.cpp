#include "ItemLogic.hpp"
#include "ObjectFile.hpp"
#include "ItemInterface.hpp"
#include <iostream>
#include <cassert>

ItemLogic::ItemLogic(const std::string oName):
	boundingBox(glm::vec3(0), glm::vec3(2)), position(glm::vec3(0)), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))), name(oName), used(false), myInterface(ItemInterface::getSingletonItemInterface())
{
  const std::string path = "items/"+name+".item";
  //Je crée un ObjectFile à partir du fichier.item et récupère un std::map
  ObjectFile itemFile(path);
  std::map<std::string, std::string> map = itemFile.getData();

  name = map["Name"];
  effect = map["Effect"] ;
}

ItemLogic::ItemLogic(const ItemLogic& other):
  boundingBox(other.boundingBox), position(other.position), orientation(other.orientation), name(other.name), effect(other.effect), used(other.used), myInterface(other.myInterface)
{}

ItemLogic::~ItemLogic(){
  update();
  myInterface = nullptr;
}

const std::string ItemLogic::getEffect(){
	assert(used == false);
	used = true;

	return effect;
}

const std::string& ItemLogic::getName(){
  return name;
}

void ItemLogic::update(){
  myInterface->noSelected();
  myInterface->setName(name);
}

void ItemLogic::launch(const glm::vec3 positionLauncher, const glm::quat orientationLauncher){
  position = positionLauncher;
  orientation = orientationLauncher;
}