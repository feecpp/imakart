#ifndef PLAYER_HPP
#define PLAYER_HPP

class ItemLogic;
class Kart;

class Player
{
public:
  explicit Player(Kart& kart);

  const Kart& getKart() const;
  Kart& getKart();

  const ItemLogic* getItem() const;
  ItemLogic* getItem();

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

private:
  Kart& myKart;
  ItemLogic* myCurrentItem;
};

#endif // PLAYER_HPP
