#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "GameEnumerations.hpp"
#include "RaceEventHandler.hpp"
#include "Player.hpp"

/**
 * @brief Classe principale d'Imakart
 * Gère le déroulement du jeu.
 */
class GameEngine
{
public:
  GameEngine();

  void init();
  void update();
  void quit();

  const GameState getState() const
    {return state;}

  void setState(GameState newState)
    {state = newState;}

  const EventHandler& getHandler() const;

private:
  GameState state;
  RaceEventHandler raceEventHandler;
  Player player;

};

#endif // GAMEENGINE_HPP
