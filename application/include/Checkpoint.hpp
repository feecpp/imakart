#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <glm/glm.hpp>

class Checkpoint {
    private :
        glm::vec3 boundaries[8];
        bool checked;
        glm::vec3 origin;
    public:
        // A checkpoint is a parallelepiped built from 8 points
        Checkpoint();
        Checkpoint(const glm::vec3 origin, const int width, const int height, const int depth);

        // Returns one of his points (determined by its index)
        glm::vec3 getPoint(const int index);

        // Returns the origin
        glm::vec3 getOrigin();

        // Used to set the bool checked variable to true if the checkpoint is validated
        void validate();
};

#endif

