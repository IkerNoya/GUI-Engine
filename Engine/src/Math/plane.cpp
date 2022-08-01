#include "plane.h"
#include <string>	
#include "../dataManager.h"
#include "gtx/quaternion.hpp"

Plane::Plane() {
}


void Plane::InitializeDebugLines(Shader& shader, Renderer* renderer) {
	_shader = shader;
	line = Line(shader, renderer);
}

void Plane::draw(float size, glm::vec3 color) {

}

std::string Plane::toString() {
	std::string normal = "(" + std::to_string(_normal.x) + ", " + std::to_string(_normal.y) + ", " + std::to_string(_normal.z) + ")";
	return std::string("normal: " + normal) + std::string("distance: " + std::to_string(_distance));
}


