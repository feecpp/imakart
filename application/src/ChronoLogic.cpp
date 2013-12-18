#include "ChronoLogic.hpp"
#include <iostream>

ChronoLogic::ChronoLogic(): timer(0.f){
}

void ChronoLogic::update(float time){
  timer += time;
  //std::cout << "timerchrono " << timer << std::endl;
}

ChronoLogic::~ChronoLogic(){

}

const bool ChronoLogic::isSelected() const{
  return true;
}

