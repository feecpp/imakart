#include "ItemGenerator.hpp"
#include "ItemLogic.hpp"
#include "ItemBox.hpp"

#include <iostream>

ItemGenerator::ItemGenerator(const glm::vec3 position):
	itemPosition(position), itemBox(ItemBox::getSingletonItemBox()), boundingBox(position, glm::vec3(1.f)){
}

ItemGenerator::~ItemGenerator(){

}

ItemLogic* ItemGenerator::getRandomItem() const{
	return itemBox->createItemInstanceRandom();
}