#ifndef SPEEDTEXTE_HPP
#define SPEEDTEXTE_HPP

#include "convert.hpp"
#include "Texte2D.hpp"

class SpeedTexte: public Texte2D{
public:
  SpeedTexte(const float* pSpeedKart); 
  ~SpeedTexte();

  void update();

private:
  const float* pCurrentSpeedKart;
};

#endif