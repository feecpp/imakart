#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include "GameEnumerations.hpp"

union GameEventData
{
  int lastSecond;
  unsigned int lapNumber;
};

struct GameEvent
{
  GameEvent(GameEventType type, GameEventData data)
    : type(type), data(data) {}

  GameEventType type;
  GameEventData data;
};

#endif // GAMEEVENT_HPP
