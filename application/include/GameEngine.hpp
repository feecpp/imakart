#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "GameEnumerations.hpp"
#include "RaceEventHandler.hpp"
#include "MenuEventHandler.hpp"
#include "Player.hpp"
#include "MenuLogic.hpp"

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

  const GameState getState() const
    {return state;}

  void setState(GameState newState)
    {state = newState;}

  void setMenu(MenuLogic* menuToSet)
    {menu = *menuToSet;}
  const EventHandler& getHandler() const;

  Player& getPlayer()
    {return player;}

  MenuLogic& getMenuLogic()
    {return menu;}

private:
  GameState state;
  RaceEventHandler raceEventHandler;
  MenuEventHandler menuEventHandler;
  Player player;
  MenuLogic menu;
};

#endif // GAMEENGINE_HPP
