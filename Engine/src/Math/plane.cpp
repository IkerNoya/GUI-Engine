#include "plane.h"
#include <string>	
#include "../dataManager.h"

Plane::Plane(glm::vec3 inNormal, glm::vec3 inPoint) {
	_normal = glm::normalize(inNormal);
	float magnitude = glm::sqrt((_normal.x * _normal.x) + (_normal.y * _normal.y) + (_normal.z * _normal.z));
	_distance = glm::abs(((_normal.x * inPoint.x) + (_normal.y * inPoint.y) + (_normal.z * inPoint.z))) / magnitude;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);

}

Plane::Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	glm::vec3 v = glm::vec3(b - a);
	glm::vec3 u = glm::vec3(c - a);

	_normal = glm::normalize(glm::cross(v, u));

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
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
}

void Plane::setNormalAndPosition(glm::vec3 normal, glm::vec3 position) {
	_normal = glm::normalize(normal);
	float magnitude = glm::sqrt((_normal.x * _normal.x) + (_normal.y * _normal.y) + (_normal.z * _normal.z));
	_distance = glm::abs(((_normal.x * position.x) + (_normal.y * position.y) + (_normal.z * position.z))) / magnitude;
}

std::string Plane::toString() {
	std::string normal = "(" + std::to_string(_normal.x) + ", " + std::to_string(_normal.y) + ", " + std::to_string(_normal.z) + ")";
	return std::string("normal: " + normal) + std::string("distance: " + std::to_string(_distance));
}
