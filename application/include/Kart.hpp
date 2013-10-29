#ifndef KART_HPP
#define KART_HPP

#include <glm/glm.hpp>
#include "Positionable.hpp"

class Kart : public Positionable
{
	private:
		glm::vec3 position;
    	glm::vec3 direction;
		float speed;

	public:
		Kart();
    Kart(glm::vec3 position, glm::vec3 direction, float speed);
		
		void moveForward();
		void moveBackward();
		void turnLeft();
		void turnRight();

    virtual const glm::vec3& getPosition() const;
    virtual const glm::vec3& getOrientation() const;
};

#endif
