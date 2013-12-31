#include "ItemInterface.hpp"

ItemInterface* ItemInterface::singletonItemInterface = NULL;

ItemInterface* ItemInterface::getSingletonItemInterface(){
  if(singletonItemInterface == NULL){
    singletonItemInterface = new ItemInterface();
  }
  return singletonItemInterface;
}

void ItemInterface::kill (){
  if (NULL != singletonItemInterface){
    delete singletonItemInterface;
    singletonItemInterface = NULL;
  }
}

ItemInterface::ItemInterface():
	used(false){}

ItemInterface::~ItemInterface(){}

const bool ItemInterface::isSelected() const{
	return used;
}

void ItemInterface::noSelected(){
	used = true;
}