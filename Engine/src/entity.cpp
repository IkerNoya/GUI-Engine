#include "entity.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"
#include "dataManager.h"
#include <iostream>
#include <forward_list>

int Entity::_nextEntityID = 0;

void Entity::updateModel() {
	modelMatrix.trs = modelMatrix.translate * modelMatrix.rotation.x * modelMatrix.rotation.y * modelMatrix.rotation.z * modelMatrix.scale;
}

Entity::Entity()
{
	_renderer = nullptr;
	modelMatrix.translate = glm::mat4(1.0);

	modelMatrix.rotation.x = glm::mat4(1.0);
	modelMatrix.rotation.y = glm::mat4(1.0);
	modelMatrix.rotation.z = glm::mat4(1.0);
	modelMatrix.scale = glm::mat4(1.0);

	SetScale(1.0f, 1.0f, 1.0f);
	SetPosition(0.0f, 0.0f, 0.0f);
	transform.rotation = glm::vec3(0);

	_id = _nextEntityID++;
}

Entity::Entity(Renderer* renderer) {

	_renderer = renderer;
	modelMatrix.translate = glm::mat4(1.0);

	modelMatrix.rotation.x = glm::mat4(1.0);
	modelMatrix.rotation.y = glm::mat4(1.0);
	modelMatrix.rotation.z = glm::mat4(1.0);
	modelMatrix.scale = glm::mat4(1.0);

	SetScale(1.0f, 1.0f, 1.0f);
	SetPosition(0.0f, 0.0f, 0.0f);
	transform.rotation = glm::vec3(0);

	_id = _nextEntityID++; // assign id and then increase the value so the next entity doesn´t share the same one
}

Entity::~Entity() {
}

Renderer* Entity::GetRenderer() {
	return _renderer;
}

glm::mat4 Entity::getModelMatrix() {
	return modelMatrix.trs;
}

glm::mat4 Entity::getLocalModelMatrix(){

	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));

	const glm::mat4 rotationMatrix = transformX * transformY * transformZ;
	return glm::translate(glm::mat4(1.0f), transform.position) * rotationMatrix * glm::scale(glm::mat4(1.0f), transform.scale);
}

void Entity::SetPosition(float x, float y, float z) {
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;
	
	modelMatrix.translate = glm::translate(glm::mat4(1.0f), transform.position);
	updateModel();
}

void Entity::updateMatrices(){
	modelMatrix.translate = glm::translate(glm::mat4(1.0f), transform.position);

	modelMatrix.rotation.x = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	modelMatrix.rotation.y = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	modelMatrix.rotation.z = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));

	modelMatrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);

	updateModel();
}

void Entity::SetScale(float x, float y, float z) {
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;

	modelMatrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);
	updateModel();
}

void Entity::SetID(int id) {
	_id = id;
}

int Entity::GetID() {
	return _id;
}

void Entity::SetName(std::string name) {
	_name = name;
}

void Entity::setEntityColor(glm::vec3 color)
{
	setColor(color);
}

void Entity::setColor(glm::vec3 color)
{
}

void Entity::setColor(float r, float g, float b)
{
}

void Entity::updateForward()
{
	transform.forward.x = glm::cos(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	transform.forward.y = glm::sin(glm::radians(transform.rotation.x));
	transform.forward.z = glm::sin(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	transform.forward = glm::normalize(transform.forward);
}

void Entity::updateUp()
{
	transform.up = glm::normalize(glm::cross(transform.right, transform.forward));
}

void Entity::updateRight()
{
	transform.right = glm::normalize(glm::cross(transform.forward, glm::vec3(0, 1, 0)));
}

void Entity::ComputeModelMatrix()
{
	modelMatrix.trs = getLocalModelMatrix();
}

void Entity::ComputeModelMatrix(const glm::mat4& parentModelMatrix)
{
	modelMatrix.trs = parentModelMatrix * getLocalModelMatrix();
}

void Entity::updateSelfAndChild()
{
	if (parent)
		ComputeModelMatrix(parent->getModelMatrix());
	else
		ComputeModelMatrix();

	for (auto&& child : children) {
		child->updateSelfAndChild();
	}
}

void Entity::updateVectors()
{
	updateForward();
	updateRight();
	updateUp();
}

std::string Entity::GetName() {
	return _name;
}


void Entity::addChild(Entity* entity)
{
	children.emplace_back(entity);
	children.back()->parent = this;
}

void Entity::setRenderer(Renderer* renderer){
	_renderer = renderer;
}
