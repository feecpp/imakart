#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "GameEnumerations.hpp"
#include "RaceEventHandler.hpp"
#include "MenuEventHandler.hpp"
#include "Player.hpp"
#include "MenuLogic.hpp"
#include "Hangar.hpp"
#include "Map.hpp"

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

  Player& getPlayer() const;
  Kart& getPlayerKart() const;

  MenuLogic& getMenuLogic()
    {return menu;}

private:
  GameState state;
  MenuLogic menu;
  Hangar hangar;
  Player* player;
  Map* map;
};

#endif // GAMEENGINE_HPP
