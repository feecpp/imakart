#ifndef CHRONOLOGIC_HPP
#define CHRONOLOGIC_HPP
#include <InterfaceElement.hpp>

class ChronoLogic : public InterfaceElement
{
public:
  ChronoLogic();
  ~ChronoLogic();
  void update(float time);
  float getTime() const
  {return timer;}
  const bool isSelected() const;
  void init();

private:
  float timer;
};

#endif // CHRONO_HPP
