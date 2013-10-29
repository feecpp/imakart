#include "Checkpoint.hpp"


Checkpoint::Checkpoint(){
    this->origin= glm::vec3(0);
    for(unsigned int i=0; i<8; ++i){
        glm::vec3 point;
        this->boundaries[i]= point;
    }
}

/*The checkpoint is represented by a parallelepiped built from one glm::vec3 which is called the origin.
 *The origin is the point at the center of the face which is at the bottom of the parallelepiped.
 *The 8 points that define the boundaries of the checkpoint are calculated from the origin and
 from 3 other parameters. Those parameters define the dimensions of the parallelepiped.
 *The boundaries are sorted : [0-3]front face : from top-left corner to bottom left corner
  ---------------------------- [4-7]back face : from top-left corner to bottom left corner
 *Improvement : add a rotation parameter ? */

Checkpoint::Checkpoint(const glm::vec3 origin, const int width, const int height, const int depth){
    this->boundaries[0] = glm::vec3(origin.x - width*0.5, origin.y + height, origin.z + depth*0.5);
    this->boundaries[1] = glm::vec3(origin.x + width*0.5, origin.y + height, origin.z + depth*0.5);
    this->boundaries[2] = glm::vec3(origin.x + width*0.5, origin.y, origin.z + depth*0.5);
    this->boundaries[3] = glm::vec3(origin.x - width*0.5, origin.y, origin.z + depth*0.5);
    this->boundaries[4] = glm::vec3(origin.x - width*0.5, origin.y + height, origin.z - depth*0.5);
    this->boundaries[5] = glm::vec3(origin.x + width*0.5, origin.y + height, origin.z - depth*0.5);
    this->boundaries[6] = glm::vec3(origin.x + width*0.5, origin.y, origin.z - depth*0.5);
    this->boundaries[7] = glm::vec3(origin.x - width*0.5, origin.y, origin.z - depth*0.5);

    this->origin= origin;
}

// Returns one of his points (determined by its index)
glm::vec3 Checkpoint::getPoint(const int index){
    return this->boundaries[index];
}

// Returns the origin
glm::vec3 Checkpoint::getOrigin(){
    return this->origin;
}

// Used to set the bool checked variable to true if the checkpoint is validated
void Checkpoint::validate(){
    this->checked = true;
}
