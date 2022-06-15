#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "gtc/matrix_transform.hpp"
#include "mat4x4.hpp"
#include "gtc/type_ptr.hpp"
#include "detail/type_mat4x4.hpp"
#include "dataManager.h"
#include "window.h"

Camera::Camera(Window* window, Renderer* renderer, ProjectionType type) : Entity(renderer) {
	_window = window;
	_view = glm::mat4(1.0f);
	_proj = glm::mat4(1.0f);
	_name = "Camera";
	_type = type;
	_worldUp = glm::vec3(0, 1, 0);
	_forward = glm::vec3(0, 0, -1);

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

Camera::~Camera() {

}

void Camera::updateView() {
	_view = glm::lookAt(transform.position, transform.position +  _forward, _up);
}

void Camera::setProjection(ProjectionType type) {
	_type = type;
	float windowWidth = static_cast<float>(_window->getWidth());
	float windowHeight = static_cast<float>(_window->getHeight());
	switch (_type)
	{
	case ProjectionType::orthographic:
		_proj = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, 0.1f, 100.0f);
		break;
	case ProjectionType::perspective:
		// FOV					      Aspect	     near   far
		_proj = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);
		break;
	default:
		break;
	}

}

void Camera::init(Shader& shader) {
	setProjection(_type);
	updateVectors();
	updateView();
	updateShader(shader);
}

glm::mat4 Camera::getView() {
	return _view;
}

glm::mat4 Camera::getProjection() {
	return _proj;
}

ProjectionType Camera::getProjectionType() {
	return _type;
}

void Camera::draw(Shader& shader) {
	updateVectors();
	updateView();

	_renderer->drawCamera(shader, GetModelMatrix(), getView(), getProjection());
}

void Camera::updateVectors()
{
	_forward.x = glm::cos(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	_forward.y = glm::sin(glm::radians(transform.rotation.x));
	_forward.z = glm::sin(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	_forward = glm::normalize(_forward);
	_right = glm::normalize(glm::cross(_forward, _worldUp));
	_up = glm::normalize(glm::cross(_right, _forward));

	//limita rotacion de pitch
	if (transform.rotation.x >= 89.9f) transform.rotation.x = 89.9f;
	if (transform.rotation.x <= -89.9f) transform.rotation.x = -89.9f;
}

void Camera::setColor(glm::vec3 color)
{
}

void Camera::setColor(float r, float g, float b)
{
}

void Camera::rotatePitch(float pitch){
	transform.rotation.x += pitch;
}

void Camera::rotateYaw(float yaw) {
	transform.rotation.y += yaw;
}


glm::vec3 Camera::getForward(){
	return _forward;
}
glm::vec3 Camera::getUp() {
	return _up;
}
glm::vec3 Camera::getRight() {
	return _right;
}

void Camera::updateShader(Shader& shader){
	unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
	unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
	unsigned int projLoc = glGetUniformLocation(shader.getID(), "proj");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(getProjection()));
}

void Camera::setDirection(glm::vec3 target){
	_inverseDirection = glm::normalize(transform.position - target);
}
