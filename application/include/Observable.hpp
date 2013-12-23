#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include "Observer.hpp"

/**
 * @brief The Observable interface
 * Permet à un objet d'être observé par un observateur
 */
class Observable
{
public:
  virtual ~Observable() {}

  virtual const void attach(Observer* obs)=0;
};

#endif // OBSERVABLE_HPP
