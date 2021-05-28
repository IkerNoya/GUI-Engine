#include "entity.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"

void Entity::updateModel() {
	model.trs = model.translate * model.rotation.x * model.rotation.y * model.rotation.z * model.scale;
}

Entity::Entity(Renderer* renderer) {
	_renderer = renderer;
	model.translate = glm::mat4(1.0);
	model.rotation.x = glm::mat4(1.0);
	model.rotation.y = glm::mat4(1.0);
	model.rotation.z = glm::mat4(1.0);
	model.scale = glm::mat4(1.0);

	setPos(1.0f, 1.0f, 1.0f);
	setXRot(0.0f);
	setYRot(0.0f);
	setZRot(0.0f);
	setScale(1.0f, 1.0f, 1.0f);
}

Entity::~Entity() {
	_renderer = NULL;
}

Renderer* Entity::getRenderer() {
	return _renderer;
}

glm::mat4 Entity::getModel() {
	return model.trs;
}

void Entity::setPos(float x, float y, float z) {
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;
	
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	updateModel();
}

void Entity::setXRot(float angle) {
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0f);
	axis[0] = 1.0f;
	axis[1] = 0;
	axis[2] = 0;
	
	model.rotation.x = glm::rotate(glm::mat4(1.0f), angle, axis);
	updateModel();
}

void Entity::setYRot(float angle) {
	transform.rotation.y = angle;
	glm::vec3 axis = glm::vec3(1.0f);
	axis[0] = 0;
	axis[1] = 1.0f;
	axis[2] = 0;

	model.rotation.x = glm::rotate(glm::mat4(1.0f), angle, axis);
	updateModel();
}

void Entity::setZRot(float angle) {
	transform.rotation.z = angle;
	glm::vec3 axis = glm::vec3(1.0f);
	axis[0] = 0;
	axis[1] = 0;
	axis[2] = 1.0f;

	model.rotation.x = glm::rotate(glm::mat4(1.0f), angle, axis);
	updateModel();
}

void Entity::setScale(float x, float y, float z) {
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;

	model.scale = glm::scale(glm::mat4(1.0f), transform.scale);
	updateModel();
}