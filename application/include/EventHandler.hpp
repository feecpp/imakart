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
  virtual void up() const = 0;

  /**
   * @brief down
   * Flèche bas
   */
  virtual void down() const = 0;

  /**
   * @brief left
   * Flèche gauche
   */
  virtual void left() const = 0;

  /**
   * @brief right
   * Flèche droite
   */
  virtual void right() const = 0;

};

#endif // EVENTMANAGER_HPP
