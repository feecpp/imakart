#ifndef OPPONENT_HPP
#define OPPONENT_HPP

#include "Checkpoint.hpp"
#include <vector>
#include <stack>
#include "GameEvent.hpp"

class Kart;

class Opponent
{
public:
  static const unsigned int MAX_LAP;
  explicit Opponent(Kart& kart, std::stack<GameEvent>& eventStack);

  const Kart& getKart() const;
  Kart& getKart();
  void startMovement();

  const unsigned int& getCurrentLap() const;
  unsigned int& getCurrentLap();

  void fillCheckpoints(const std::vector<Checkpoint> checkpoints);
  void validateCheckpoints();

private:
  Kart& opponentKart;
  std::stack<GameEvent>& eventStack;
  std::vector<Checkpoint> checkpoints;
  unsigned int currentLap;
  bool newLapNextTime;
  Checkpoint lastCheckPointChecked;
};

#endif // OPPONENT_HPP
