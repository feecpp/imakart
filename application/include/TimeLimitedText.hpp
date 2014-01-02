#ifndef TIMELIMITEDTEXT_HPP
#define TIMELIMITEDTEXT_HPP

#include "Object2D.hpp"
#include "Texte2D.hpp"
#include <SFML/System.hpp>

class TimeLimitedText : public Object2D
{
public:

  TimeLimitedText(const std::string& textString, float durationInMillis, glm::vec2 position)
    : text(textString), durationInMillis(durationInMillis), active(false)
  {
    text.setPosition(position.x, position.y, 50);
  }

  void start()
  {
    clock.restart();
    active = true;
  }

  virtual void draw(const glimac::ShaderProgram& program) const
  {
    if (!active)
      return;

    text.draw(program);
  }

  virtual void update()
  {
    if (active)
    {
      active = ! isFinished();
    }
  }

  bool isFinished() const
  {
    return clock.getElapsedTime().asMilliseconds() > durationInMillis;
  }

private:
  Texte2D text;
  sf::Clock clock;
  float durationInMillis;
  bool active;
};

#endif // TIMELIMITEDTEXT_HPP
