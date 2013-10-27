#ifndef DRAWER_HPP
#define DRAWER_HPP

namespace
{

class Drawer
{
public:
  virtual void draw() = 0;
};

class SimpleDrawer : public Drawer
{
public:
  SimpleDrawer();
  ~SimpleDrawer();

  virtual void draw();
};

} // namespace glimac

#endif // DRAWER_HPP
