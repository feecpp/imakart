#include "ItemLogic.hpp"
#include <iostream>
#include <cassert>

ItemLogic::ItemLogic(const int effect):
	numEffect(effect), used(false)
	{}

ItemLogic::~ItemLogic(){}

const int ItemLogic::getEffect(){
	assert(used == false);
	used = true;

	return numEffect;
}