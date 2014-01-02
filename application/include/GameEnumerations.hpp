#ifndef GAMEENUMERATIONS_HPP
#define GAMEENUMERATIONS_HPP

/**
 * @brief Représente l'état courant du jeu
 */
enum GameState
{
  NO_STATE,
  IN_MENU,
  IN_MENU_OPTIONS,
  IN_MENU_KART,
  IN_MENU_MAP,
  PREPARING_RACE,
  BEFORE_RACE_BEGIN,
  IN_RACE,
  IN_RACE_MENU
};

enum GameEventType
{
  RACE_BEGIN,
  COUNTER_UPDATE,
  NEW_LAP
};

#endif // GAMEENUMERATIONS_HPP
