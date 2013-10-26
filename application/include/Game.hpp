#ifndef GAME_HPP
#define GAME_HPP

#include "GameEnumerations.hpp"
#include "RaceEventHandler.hpp"
#include "Player.hpp"

/**
 * @brief Classe principale d'Imakart
 * Gère le déroulement du jeu.
 */
class Game
{
public:
  Game();

  void init();
  void update();
  void quit();

  const GameState getState() const
    {return state;}

  void setState(GameState newState)
    {state = newState;}

  const EventHandler& getHandler();

private:
  GameState state;
  RaceEventHandler raceEventHandler;
  Player player;

};

#endif // GAME_HPP
