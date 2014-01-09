#include "ItemGenerator.hpp"
#include "ItemLogic.hpp"
#include "ItemBox.hpp"

#include <iostream>

ItemGenerator::ItemGenerator(const glm::vec3 position):
  itemPosition(position), itemOrientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))), itemBox(ItemBox::getSingletonItemBox()), boundingBox(position, glm::vec3(1.f)), visible(true), time(0.f){
}

ItemGenerator::~ItemGenerator(){

}

ItemLogic* ItemGenerator::getRandomItem() const{
  return itemBox->createItemInstanceRandom();
}

void ItemGenerator::setNotVisible(){
  if(visible){
    visible = false;
	time = 700;
  }
}

void ItemGenerator::update(){
  if(!visible)
  {
  	time -= 1;
  }

  if(time <= 0 && !visible)
  {
  	visible = true;
  }
}