#include "Chrono.hpp"
#include <iostream>

Chrono::Chrono(): timer(0.f){
}

void Chrono::update(float time){
  timer += time;
  //std::cout << "timerchrono " << timer << std::endl;
}

Chrono::~Chrono(){

}

