#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <glm/glm.hpp>

/** Un checkpoint est une aire circulaire sur une map
 *  par laquelle le joueur est obligé de passer pour valider
 *  un tour de circuit.
 * @see Map
 **/
struct Checkpoint
{
  glm::vec3 position;
  float radius;
  bool checked;
  bool start; //Indique que c'est le point de départ du circuit

  bool contains(const glm::vec3& point)
  {
    if (glm::length(point - position) < radius)
      return true;
    else
      return false;
  }
};

#endif

