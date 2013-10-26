#include "Checkpoint.hpp"


Checkpoint::Checkpoint(){
    this->origin= Point3D();
    for(unsigned int i=0; i<8; ++i){
        Point3D point;
        this->boundaries[i]= point;
    }
}

/*The checkpoint is represented by a parallelepiped built from one Point3D which is called the origin.
 *The origin is the point at the center of the face which is at the bottom of the parallelepiped.
 *The 8 points that define the boundaries of the checkpoint are calculated from the origin and
 from 3 other parameters. Those parameters define the dimensions of the parallelepiped.
 *The boundaries are sorted : [0-3]front face : from top-left corner to bottom left corner
  ---------------------------- [4-7]back face : from top-left corner to bottom left corner
 *Improvement : add a rotation parameter ? */

Checkpoint::Checkpoint(const Point3D origin, const int width, const int height, const int depth){
    this->boundaries[0] = Point3D(origin.x - width/2.0, origin.y + height, origin.z + depth/2.0);
    this->boundaries[1] = Point3D(origin.x + width/2.0, origin.y + height, origin.z + depth/2.0);
    this->boundaries[2] = Point3D(origin.x + width/2.0, origin.y, origin.z + depth/2.0);
    this->boundaries[3] = Point3D(origin.x - width/2.0, origin.y, origin.z + depth/2.0);
    this->boundaries[4] = Point3D(origin.x - width/2.0, origin.y + height, origin.z - depth/2.0);
    this->boundaries[5] = Point3D(origin.x + width/2.0, origin.y + height, origin.z - depth/2.0);
    this->boundaries[6] = Point3D(origin.x + width/2.0, origin.y, origin.z - depth/2.0);
    this->boundaries[7] = Point3D(origin.x - width/2.0, origin.y, origin.z - depth/2.0);

    this->origin= origin;
}

// Returns one of his points (determined by its index)
Point3D Checkpoint::getPoint(const int index){
    return this->boundaries[index];
}

// Returns the origin
Point3D Checkpoint::getOrigin(){
    return this->origin;
}

// Used to set the bool checked variable to true if the checkpoint is validated
void Checkpoint::validate(){
    this->checked = true;
}
