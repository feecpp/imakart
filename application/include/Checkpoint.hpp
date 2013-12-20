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
};

#endif

