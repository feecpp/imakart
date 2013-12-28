#ifndef OPPONENT_HPP
#define OPPONENT_HPP

class Kart;

class Opponent
{
public:
  explicit Opponent(Kart& kart);

  const Kart& getKart() const;
  Kart& getKart();
  void startMovement();

private:
  Kart& opponentKart;
};

#endif // OPPONENT_HPP
