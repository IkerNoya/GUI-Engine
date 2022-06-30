#ifndef PLANE_H
#define PLANE_H

#include "../export.h"
#include "glm.hpp"
#include <iostream>
#include "../entity.h"

struct ENGINE_API Plane : public Entity{
private: 
	glm::vec3 _normal;
	float _distance;

public:
	Plane(glm::vec3 inNormal, glm::vec3 inPoint);
	Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c);

	glm::vec3 closestPointInPlane(glm::vec3 point);
	void flip();
	float getDistanceToPoint(glm::vec3 point);
	bool getSide(glm::vec3 point);
	bool sameSide(glm::vec3 pointA, glm::vec3 pointB);
	void set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);

	void setNormalAndPosition(glm::vec3 normal, glm::vec3 position);

	std::string toString();

	inline glm::vec3 getNormal() const { return _normal; }
	inline float getDistance() const { return _distance; }
};

#endif // !PLANE_H

