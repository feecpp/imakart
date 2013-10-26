#ifndef MENUEVENTHANDLER_HPP
#define MENUEVENTHANDLER_HPP

class GameEngine;

class MenuEventHandler : public EventHandler
{
public:
  MenuEventHandler(GameEngine* gameEngine)
    : gameEngine(gameEngine) {}

  virtual void up() const {}
  virtual void down() const {}
  virtual void left() const {}
  virtual void right() const {}

private:
  GameEngine* gameEngine;
};

#endif // MENUEVENTHANDLER_HPP
