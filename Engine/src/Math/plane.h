#ifndef PLANE_H
#define PLANE_H

#include "../export.h"
#include "glm.hpp"
#include <iostream>
#include "../entity.h"
#include "../debug.h"

class Line;

struct ENGINE_API Plane : public Entity{
private: 
	Shader _shader;
	Line line;
public:
	glm::vec3 normal = glm::vec3(0,1,0);
	float distance = 0;
	Plane(){}

	Plane(const glm::vec3& p1, const glm::vec3& norm)
		: normal(glm::normalize(norm)),
		distance(glm::dot(normal, p1)) {
	}

	float getSignedDistanceToPlan(const glm::vec3& point) const {
		return glm::dot(normal, point) - distance;
	}
	void InitializeDebugLines(Shader& shader, Renderer* renderer);

	void draw(float size, glm::vec3 color);
	std::string toString();
};

#endif // !PLANE_H

