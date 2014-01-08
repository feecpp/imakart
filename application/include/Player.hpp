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

  const Kart& getKart() const;
  Kart& getKart();

  const ItemLogic& getItem() const;
  ItemLogic& getItem();

  const bool hasItem() const;

  const unsigned int& getCurrentLap() const;
  unsigned int& getCurrentLap();

  void fillCheckpoints(const std::vector<Checkpoint> checkpoints);
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

private:
  Kart& myKart;
  std::stack<GameEvent>& eventStack;

  ItemLogic* myCurrentItem;

  //Gestion des tours / checkpoints
  //Contient une copie des checkpoints de la map en cours (vide si en dehors d'une course)
  std::vector<Checkpoint> checkpoints;
  unsigned int currentLap;
  bool newLapNextTime;
  Checkpoint lastCheckPointChecked;

};

#endif // PLAYER_HPP
