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
#include "Opponent.hpp"
#include "Observable.hpp"
#include <vector>

/**
 * @brief Classe principale d'Imakart
 * Gère le déroulement du jeu. C'est le GameEngine
 * qui gère le temps dans la simulation.
 */
class GameEngine : public Observable
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

  void switchPause()
    {pause = !pause;}

  const bool inPause() const
    {return pause;}

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

  //Création des adversaires
  void setupOpponents(unsigned int nbOpponents);
  Opponent& getOpponent(unsigned int id) const;
  Kart& getOpponentKart(unsigned int id) const;

  ///Le GameEngine devient responsable de la memoire liee a ce pointeur
  void setCurrentMap(Map* newMap);
  Map& getCurrentMap() const;

  ChronoLogic& getChrono() const;

  MenuLogic& getMenuLogic()
    {return menu;}

  virtual const void attach(Observer* obs);

private:
  void doPhysic();
  static const char TURN_DURATION_IN_MILLIS = 20;

  GameState state;
  MenuLogic menu;
  //Hangar hangar;
  Player* player;
  std::vector<Opponent*> opponents;
  Map* currentMap;
  sf::Clock clock;
  ChronoLogic* chrono;
  Observer* scenario;
  bool exitFlag;
  bool pause;
  float buffer;

  ///Pour la gestion du temps
  float lag;
};

#endif // GAMEENGINE_HPP
