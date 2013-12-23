#ifndef OBSERVER_HPP
#define OBSERVER_HPP

/**
 * @brief The Observer interface
 * Permet à un objet d'observer un observable
 */
class Observer
{
public:
  virtual ~Observer() {}

  virtual void update(std::string notification)=0;
};


#endif // OBSERVER_HPP
