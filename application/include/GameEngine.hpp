#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "GameEnumerations.hpp"
#include "RaceEventHandler.hpp"
#include "MenuEventHandler.hpp"
#include "Player.hpp"
#include "MenuLogic.hpp"
#include "Hangar.hpp"
#include "Map.hpp"
#include <SFML/System.hpp>
#include "ChronoLogic.hpp"
/**
 * @brief Classe principale d'Imakart
 * Gère le déroulement du jeu. C'est le GameEngine
 * qui gère le temps dans la simulation.
 */
class GameEngine
{
public:
  GameEngine();
  ~GameEngine();

  void init();
  void update();

  const GameState getState() const
    {return state;}

  void setState(GameState newState)
    {state = newState;}

  void setMenu(MenuLogic* menuToSet)
    {menu = *menuToSet;}

  /**
   * @brief setExitFlag indique que le jeu va quitter
   * (la fonction getExitFlag() renvoie true)
   */
  void activateExitFlag();
  void deactivateExitFlag();
  bool getExitFlag() const;

  //Le player n'existe pas (=nullptr) tant que cette fonction n'est pas appelee
  void setupPlayer(const std::string& playerKartName);
  Player& getPlayer() const;
  Kart& getPlayerKart() const;
  Map& getMap() const;
  ChronoLogic& getChrono() const;

  const Hangar& getHangar() const
    {return hangar;}

  Hangar& getHangar()
    {return hangar;}

  MenuLogic& getMenuLogic()
    {return menu;}

private:
  GameState state;
  MenuLogic menu;
  Hangar hangar;
  Player* player;
  Map* map;
  sf::Clock clock;
  ChronoLogic* chrono;
  bool exitFlag;
};

#endif // GAMEENGINE_HPP
