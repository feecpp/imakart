#ifndef OPPONENT_HPP
#define OPPONENT_HPP

#include "Checkpoint.hpp"
#include <vector>

class Kart;

class Opponent
{
public:
  explicit Opponent(Kart& kart);
  void init(unsigned int i, std::vector<glm::vec3> startingPoints);

  const Kart& getKart() const;

  const float getProgression()const
    {return progression;}

  const int getNextCheck()const
    {return nextCheck;}

  const unsigned int getCurrentLap()const
    {return currentLap;}
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
  float progression;
  unsigned int currentLap;
  bool trigger;
};

#endif // OPPONENT_HPP
