#ifndef LAPTEXT_HPP
#define LAPTEXT_HPP

#include "convert.hpp"
#include "Texte2D.hpp"

class LapText: public Texte2D{
public:
  LapText(const unsigned int& currentLap); 
  ~LapText();

  void update();

private:
  const unsigned int& currentLap;
};

#endif