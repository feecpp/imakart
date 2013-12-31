#include "ItemLogic.hpp"
#include "ObjectFile.hpp"
#include "ItemInterface.hpp"
#include <iostream>
#include <cassert>

ItemLogic::ItemLogic(const std::string oName):
	name(oName), used(false), myInterface(ItemInterface::getSingletonItemInterface())
{
  const std::string path = "items/"+name+".item";

  //Je crée un ObjectFile à partir du fichier.item et récupère un std::map
  ObjectFile itemFile(path);
  std::map<std::string, std::string> map = itemFile.getData();

  name = map["Name"];
  effect = map["Effect"] ;
}

ItemLogic::~ItemLogic(){
  update();
  myInterface = nullptr;
}

const std::string ItemLogic::getEffect(){
	assert(used == false);
	used = true;

	return effect;
}

void ItemLogic::update(){
  myInterface->noSelected();
}