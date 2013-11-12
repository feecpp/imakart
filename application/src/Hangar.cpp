#include "Hangar.hpp"
#include "Kart.hpp"

Hangar::Hangar()
{
  playerKart = new Kart();
}

Hangar::~Hangar()
{
  delete playerKart;
}

Kart& Hangar::getPlayerKart() const
{
  return *playerKart;
}
