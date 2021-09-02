#include "entity.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"
#include "dataManager.h"

int Entity::_nextEntityID = 0;

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

	setPosition(1.0f, 1.0f, 1.0f);
	setXRot(0.0f);
	setYRot(0.0f);
	setZRot(0.0f);
	setScale(1.0f, 1.0f, 1.0f);

	_id = _nextEntityID++; // assign id and then increase the value so the next entity doesn�t share the same one
}

Entity::~Entity() {
}

Renderer* Entity::getRenderer() {
	return _renderer;
}

glm::mat4 Entity::getModel() {
	return model.trs;
}

void Entity::setPosition(float x, float y, float z) {
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;
	
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	updateModel();
}

void Entity::updateMatrices(){
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	model.scale = glm::scale(glm::mat4(1.0f), transform.scale);

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

void Entity::setID(int id) {
	_id = id;
}

int Entity::getID() {
	return _id;
}

void Entity::setName(std::string name) {
	_name = name;
}

std::string Entity::getName() {
	return _name;
}
