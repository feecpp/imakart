#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Checkpoint.hpp"
#include <vector>
#include <stack>
#include "GameEvent.hpp"

class ItemLogic;
class Kart;

class Player
{
public:
  static const unsigned int MAX_LAP;

  explicit Player(Kart& kart, std::stack<GameEvent>& eventStack);
  void init(unsigned int i, std::vector<glm::vec3> startingPoints);

  const Kart& getKart() const;
  Kart& getKart();

  const ItemLogic& getItem() const;
  ItemLogic& getItem();

  const float getProgression()const
    {return progression;}
  const int getNextCheck()const
    {return nextCheck;}
  int& getRank()
    {return rank;}
  void setRank(int nb)
    {rank = nb;}

  const bool hasItem() const;

  const unsigned int& getCurrentLap() const;
  unsigned int& getCurrentLap();

  void fillCheckpoints(const std::vector<Checkpoint> checkpoints);
  void fillOpponentCheckpoints(const std::vector<Checkpoint> checkpoints);
  void validateCheckpoints();

  void moveForward() const;
  void moveBackward() const;
  void turnLeft() const;
  void turnRight() const;
  void stopMove() const;
  void stopTurning() const;
  void brake() const;
  void drift() const;

  void setItem(ItemLogic* newItem);
  void useItem();
  void launchItem();

  void switchInBackwardView()
    {viewBackward = true;}
  void switchInForwardView()
    {viewBackward = false;}

private:
  Kart& myKart;
  std::stack<GameEvent>& eventStack;

  ItemLogic* myCurrentItem;

  //Gestion des tours / checkpoints
  //Contient une copie des checkpoints de la map en cours (vide si en dehors d'une course)
  std::vector<Checkpoint> checkpoints;
  std::vector<Checkpoint> opponentCheckpoints;
  unsigned int currentLap;
  bool newLapNextTime;
  float progression;
  int nextCheck;
  int rank;
  bool viewBackward;
};

#endif // PLAYER_HPP
