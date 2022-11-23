#include "entity.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"
#include "dataManager.h"
#include <iostream>
#include <forward_list>
#include "gtc/quaternion.hpp"
#include <gtx/quaternion.hpp>

int Entity::_nextEntityID = 0;
float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;

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
	modelMatrix.trs = glm::mat4(1);
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
	//SetPosition(0.0f, 0.0f, 0.0f);
	modelMatrix.trs = glm::mat4(1);
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

	const glm::mat4 rotationMatrix = glm::toMat4(transform.rotationQuat);
	return glm::translate(glm::mat4(1.0f), transform.position) * rotationMatrix * glm::scale(glm::mat4(1.0f), transform.scale);
}

void Entity::SetPosition(float x, float y, float z) {
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;
	
	modelMatrix.translate = glm::translate(glm::mat4(1.0f), transform.position);
	updateModel();
	updateVectors();
}

void Entity::updateMatrices(){
	modelMatrix.translate = glm::translate(glm::mat4(1.0f), transform.position);

	modelMatrix.rotation.x = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	modelMatrix.rotation.y = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	modelMatrix.rotation.z = glm::rotate(glm::mat4(1.0), glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));

	modelMatrix.rotMatrix = glm::toMat4(transform.rotationQuat);

	modelMatrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);

	updateModel();
}

void Entity::SetScale(float x, float y, float z) {
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;

	modelMatrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);
	updateModel();
	updateVectors();
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
	/*updateForward();
	updateRight();
	updateUp();*/
	transform.rotationQuat = EulerToQuat(transform.rotation);
	transform.forward = QuatXVec(transform.rotationQuat, glm::vec3(0, 0, 1));
	transform.up = QuatXVec(transform.rotationQuat, glm::vec3(0, 1, 0));
	transform.right = QuatXVec(transform.rotationQuat, glm::vec3(1, 0, 0));
}

void Entity::setParent(Entity* newParent)
{
	parent = newParent;
}

void Entity::setIsParent(bool isParent)
{
	_isParent = isParent;
}

std::string Entity::GetName() {
	return _name;
}

void Entity::show(bool value)
{
	_shouldDraw = value;
	if (children.size() <= 0 || _shouldDraw) return;

	for (auto* child : children) {
		if (child) {
			child->show(value);
		}
	}
}

glm::quat Entity::EulerToQuat(glm::vec3 euler)
{
	euler *= deg2rad;

	float cy = cos(euler.z * 0.5);
	float sy = sin(euler.z * 0.5);
	float cp = cos(euler.x * 0.5);
	float sp = sin(euler.x * 0.5);
	float cr = cos(euler.y * 0.5);
	float sr = sin(euler.y * 0.5);

	glm::quat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = cr * sp * cy + sr * cp * sy;
	q.y = sr * cp * cy - cr * sp * sy;
	q.z = cr * cp * sy - sr * sp * cy;
	return q;
}

glm::vec3 Entity::QuatXVec(glm::quat quat, glm::vec3 vec)
{
	float x2 = quat.x * 2.0f;
	float y2 = quat.y * 2.0f;
	float z2 = quat.z * 2.0f;
	float xx2 = quat.x * x2;
	float yy2 = quat.y * y2;
	float zz2 = quat.z * z2;
	float xy2 = quat.x * y2;
	float xz2 = quat.x * z2;
	float yz2 = quat.y * z2;
	float wx2 = quat.w * x2;
	float wy2 = quat.w * y2;
	float wz2 = quat.w * z2;

	glm::vec3 res;
	res.x = (1.0f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
	res.y = (xy2 + wz2) * vec.x + (1.0f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
	res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.0f - (xx2 + yy2)) * vec.z;
	return res;
}


void Entity::addChild(Entity* entity)
{
	children.emplace_back(entity);
	children.back()->parent = this;
}

void Entity::setRenderer(Renderer* renderer){
	_renderer = renderer;
}

void Entity::setShader(Shader& shader) {
}

void Entity::SetRot(float x, float y, float z)
{
	transform.rotation = glm::vec3(x, y, z);
	updateVectors();
	updateMatrices();
}

void Entity::SetRot(glm::vec3 euler)
{
	transform.rotation = euler;
	updateVectors();
	updateMatrices();
}

void Entity::SetRot(glm::quat quaternion)
{
	transform.rotationQuat = quaternion;
	updateVectors();
	updateMatrices();
}
