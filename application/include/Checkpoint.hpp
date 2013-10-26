#pragma once

#include "Point3D.hpp"

class Checkpoint {
    private :
        Point3D boundaries[8];
        bool checked;
        Point3D origin;
    public:
        // A checkpoint is a parallelepiped built from 8 points
        Checkpoint();
        Checkpoint(const Point3D origin, const int width, const int height, const int depth);

        // Returns one of his points (determined by its index)
        Point3D getPoint(const int index);

        // Returns the origin
        Point3D getOrigin();

        // Used to set the bool checked variable to true if the checkpoint is validated
        void validate();
};


