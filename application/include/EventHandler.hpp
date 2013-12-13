#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "GameEnumerations.hpp"

/**
 * @brief The EventHandler interface
 * Toutes les classes qui ont pour tache de gérer les évènements utilisateurs
 * doivent implémenter cette interface. Elle définit un comportement pour chaque
 * touche clavier pressée (si elle est gérée par le jeu)
 * A mettre à jour dès qu'on rajoute la gestion d'une touche.
 */
class EventHandler
{
public:

  /**
   * @brief up
   * Flèche haut
   */
  virtual void pressUp() const = 0;
  virtual void releaseUp() const = 0;

  /**
   * @brief down
   * Flèche bas
   */
  virtual void pressDown() const = 0;
  virtual void releaseDown() const = 0;

  /**
   * @brief left
   * Flèche gauche
   */
  virtual void pressLeft() const = 0;
  virtual void releaseLeft() const = 0;

  /**
   * @brief right
   * Flèche droite
   */
  virtual void pressRight() const = 0;
  virtual void releaseRight() const = 0;
  
  /**
   * @brief press enter
   * Touche entrée
   */
  virtual void pressEnter() const = 0;
  virtual void releaseEnter() const = 0;

  /**
   * @brief pressSpace
   * Barre espace
   */
  virtual void pressSpace() const = 0;
  virtual void releaseSpace() const = 0;
   
};

#endif // EVENTMANAGER_HPP
