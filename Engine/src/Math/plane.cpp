#include "plane.h"
#include <string>	
#include "../dataManager.h"
#include "gtx/quaternion.hpp"

Plane::Plane() {
}

Plane::Plane(glm::vec3 inNormal, glm::vec3 inPoint) {
	_normal = glm::normalize(inNormal);
	float magnitude = glm::sqrt((_normal.x * _normal.x) + (_normal.y * _normal.y) + (_normal.z * _normal.z));
	_distance = glm::abs(((_normal.x * inPoint.x) + (_normal.y * inPoint.y) + (_normal.z * inPoint.z))) / magnitude;

	_centroid = inPoint;
}

Plane::Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	glm::vec3 v = glm::vec3(b - a);
	glm::vec3 u = glm::vec3(c - a);

	_normal = glm::normalize(glm::cross(v, u));
	glm::vec3 xd = glm::cross(v, u);
	std::cout << "v: " << v.x << " | " << v.y << " | " << v.z << std::endl;
	std::cout << "u: " << u.x << " | " << u.y << " | " << u.z << std::endl;
	std::cout << "cross: " << xd.x << " | " << xd.y << " | " << xd.z << std::endl;
	std::cout << "normal: " << _normal.x << " | " << _normal.y << " | " << _normal.z << std::endl;


	_centroid = (a + b + c) / glm::vec3(3);
}

glm::vec3 Plane::closestPointInPlane(glm::vec3 point) {
	return glm::vec3();
}

void Plane::flip() {
	_normal = -_normal;
	_distance = -_distance;
}

float Plane::getDistanceToPoint(glm::vec3 point) {
	float magnitude = glm::sqrt((_normal.x * _normal.x) + (_normal.y * _normal.y) + (_normal.z * _normal.z));
	return ((_normal.x * point.x) + (_normal.y * point.y) + (_normal.z * point.z)) + _distance / magnitude;
}

bool Plane::getSide(glm::vec3 point) {
	float tempDistance = getDistanceToPoint(point);

	if (tempDistance > 0)
		return true;
	else
		return false;
}

bool Plane::sameSide(glm::vec3 pointA, glm::vec3 pointB) {
	if (getSide(pointA) == getSide(pointB))
		return true;
	else
		return false;
}

void Plane::set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	glm::vec3 v = glm::vec3(b - a);
	glm::vec3 u = glm::vec3(c - a);

	_normal = glm::normalize(glm::cross(v, u));
	float magnitude = glm::sqrt((_normal.x * _normal.x) + (_normal.y * _normal.y) + (_normal.z * _normal.z));
	_distance = glm::abs(((_normal.x * a.x) + (_normal.y * a.y) + (_normal.z * a.z))) / magnitude;

	_centroid = (a + b + c) / glm::vec3(3);
}

void Plane::setNormalAndPosition(glm::vec3 normal, glm::vec3 position) {
	_normal = glm::normalize(normal);
	float magnitude = glm::sqrt((_normal.x * _normal.x) + (_normal.y * _normal.y) + (_normal.z * _normal.z));
	_distance = glm::abs(((_normal.x * position.x) + (_normal.y * position.y) + (_normal.z * position.z))) / magnitude;
}

void Plane::setShader(Shader& shader) {
	_shader = shader;
	line = Line(_shader);
}

void Plane::draw(float size, glm::vec3 color) {
	glm::quat basis = LookRotation(_normal, glm::vec3(0, 1, 0));
	glm::vec3 scale = glm::vec3(1) * size / glm::vec3(10);
	glm::vec3 rightVector = glm::vec3(1, 0, 0);
	glm::vec3 right = glm::vec3(glm::vec3((basis.x * rightVector.x) * scale.x, (basis.y * rightVector.y) * scale.y, (basis.z * rightVector.z) * scale.z));
	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 up = glm::vec3(glm::vec3((basis.x * upVector.x) * scale.x, (basis.y * upVector.y) * scale.y, (basis.z * upVector.z) * scale.z));
	std::cout << "basis: " << scale.x << " | " << scale.y << " | " << scale.z << std::endl;

	for (int i = -5; i <= 5; i++) {
		line.draw(_centroid + (right * glm::vec3(i)) - (up * glm::vec3(5)), _centroid + (right * glm::vec3(i)) + (up * glm::vec3(5)), color);
		line.draw(_centroid + (up * glm::vec3(i)) - (right * glm::vec3(5)), _centroid+ (up * glm::vec3(i)) + (right * glm::vec3(5)), color);
		glm::vec3 xd1 = right;
		glm::vec3 xd2 = _centroid + (right * glm::vec3(i)) + (up * glm::vec3(5));
		//std::cout << "xd1: " << xd1.x << " | " << xd1.y << " | " << xd1.z << std::endl;
		//std::cout << "xd2: " << xd2.x << " | " << xd2.y << " | " << xd2.z << std::endl;
	}
}

std::string Plane::toString() {
	std::string normal = "(" + std::to_string(_normal.x) + ", " + std::to_string(_normal.y) + ", " + std::to_string(_normal.z) + ")";
	return std::string("normal: " + normal) + std::string("distance: " + std::to_string(_distance));
}

glm::quat Plane::FromToRotation(glm::vec3 from, glm::vec3 to) {
	glm::vec3 cross = glm::cross(from, to);
	//identity
	glm::quat result = glm::quat(1, 0, 0, 0);
	result.x = cross.x; 
	result.y = cross.y;
	result.z = cross.z;
	float fromMagnitude = glm::sqrt((from.x * from.x) + (from.y * from.y) + (from.z * from.z));
	float toMagnitude = glm::sqrt((to.x * to.x) + (to.y * to.y) + (to.z * to.z));
	result.w = glm::sqrt(fromMagnitude * fromMagnitude) * glm::sqrt(toMagnitude * toMagnitude) + glm::dot(from, to);
	glm::quat normalizedResult = glm::normalize(result);
	return normalizedResult;
}

glm::quat Plane::LookRotation(glm::vec3 forward, glm::vec3 up) {
	glm::quat result;
	if (forward == glm::vec3(0)) {
		result = glm::quat(1, 0, 0, 0);
		return result;
	}
	if(up != forward){
		glm::vec3 normalizedUp = glm::normalize(up);
		glm::vec3 a = forward + normalizedUp * -glm::dot(forward, normalizedUp);
		glm::quat q = FromToRotation(glm::vec3(0, 0, -1), a);
		return FromToRotation(a, forward) * a;
	}
	else {
		return FromToRotation(glm::vec3(0, 0, -1), forward);
	}
	return glm::quat();
}


