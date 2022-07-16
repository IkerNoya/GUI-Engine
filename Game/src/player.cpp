#include "player.h"
#include "camera.h"
#include "renderer.h"

Player::Player(Camera* camera, Shader& shader, Renderer* renderer, float speed, bool firstPerson)
{
	//playerModel = new Model(renderer, shader, "res/models/nanosuit/nanosuit.obj", false, "player");
	_camera = camera;
	_isFirstPerson = firstPerson;
}

Player::~Player()
{
	if (playerModel) {
		delete playerModel;
		playerModel = nullptr;
	}
}

void Player::SetPosition(glm::vec3 pos)
{
	//if (_isFirstPerson) {
	//	//playerModel->SetPosition(pos.x, pos.y, pos.z);
		_camera->transform.position = pos;
	//}
	//else {

	//}
}

void Player::MoveForward(float value)
{
	glm::vec3 direction = _camera->getForward();
	//if (_isFirstPerson) {
	//	direction.y = 0;
	//	//playerModel->transform.position += direction *  value;
	_camera->transform.position += direction * value;
	//}
	//else {

	//}
}

void Player::MoveRight(float value)
{
	glm::vec3 direction = _camera->getRight();
	//if (_isFirstPerson) {
	//	direction.y = 0;
	//	//playerModel->transform.position += direction * value;
	_camera->transform.position += direction * value;
	//}
	//else {

	//}
}

void Player::LookRight(float value)
{
	//if (_isFirstPerson) {
	_camera->rotationSpeed = value;
	_camera->rotateYaw(_camera->rotationSpeed);
	//}
	//else {

	//}
}

void Player::LookUp(float value)
{
	//if (_isFirstPerson) {
	_camera->rotationSpeed = value;
	_camera->rotatePitch(_camera->rotationSpeed);
	//}
	//else {

	//}
}

void Player::SpectatorCameraInputs(float value) {
	glm::vec3 direction = _camera->getUp();
	_camera->transform.position += direction * value;
}
