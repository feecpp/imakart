#ifndef OPPONENT_HPP
#define OPPONENT_HPP

#include "Checkpoint.hpp"
#include <vector>

class Kart;

class Opponent
{
public:
  explicit Opponent(Kart& kart);

  const Kart& getKart() const;
  Kart& getKart();
  void startMovement();
  void touched();
  
  void fillCheckpoints(const std::vector<Checkpoint> checkpoints);
  void validateCheckpoints();

private:
  Kart& opponentKart;
  std::vector<Checkpoint> checkpoints;
  float angle;
  float heading;
  float x, z;
  int nextCheck;
};

#endif // OPPONENT_HPP
