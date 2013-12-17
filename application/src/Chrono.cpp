#include "Chrono.hpp"

Chrono::Chrono(): timer(0.f){
}

void Chrono::update(float time){
  timer += time;
}

Chrono::~Chrono(){

}

