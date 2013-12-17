#ifndef CHRONO_HPP
#define CHRONO_HPP

class Chrono
{
public:
  Chrono();
  ~Chrono();

  void update(float time);
  float getTime() const
  {return timer;}

private:
  float timer;
};

#endif // CHRONO_HPP
