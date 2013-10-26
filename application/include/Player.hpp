#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Camera.hpp"
#include "Kart.hpp"

class Player
{
public:
  Kart& getKart()
    {return playerKart;}

  const Camera& getCamera() const;


private:
  Kart playerKart;
};

#endif // PLAYER_HPP
