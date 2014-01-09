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
#include <stack>
#include "GameEvent.hpp"

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

  std::stack<GameEvent>& getEvents()
    {return eventStack;}

  const GameState getState() const
    {return state;}

  void setState(GameState newState)
    {state = newState;}

  void setMenu(MenuLogic* menuToSet)
    {menu = *menuToSet;}

  void switchPause();

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
  std::vector<Opponent*> getOpponents() const{
    return opponents;
  }

  //Item sur la map, il devient responsable de la mémoire liée à ce pointeur
  void setNewItemOnMap(ItemLogic* newItem);

  ///Le GameEngine devient responsable de la memoire liee a ce pointeur
  void setCurrentMap(Map* newMap);
  Map& getCurrentMap() const;

  std::string getSelectMapName() const;
  void setMapName(const std::string newMapName);

  ChronoLogic& getChrono() const;

  MenuLogic& getMenuLogic()
    {return menu;}

private:
  void doPhysic();
  static const char TURN_DURATION_IN_MILLIS = 20;

  //sf::Music backgroundMusic;

  GameState state;
  MenuLogic menu;
  std::stack<GameEvent> eventStack;

  Player* player;
  std::vector<Opponent*> opponents;
  std::map<int, ItemLogic*> itemsOnMap;
  Map* currentMap;
  std::string selectMapName;
  sf::Clock clock;
  ChronoLogic* chrono;
  Observer* scenario;
  bool exitFlag;
  bool pause;
  float buffer;

  ///Pour la gestion du temps
  float lag;

  //Gestion compte à rebours du départ
  int lastSecond;
  sf::Clock counter;
  bool counterStarted;

  //Gestion de la fin
  sf::Clock finishTimer;
  bool finishTimerStarted;
};

std::vector<std::string> findMapFiles();

#endif // GAMEENGINE_HPP
