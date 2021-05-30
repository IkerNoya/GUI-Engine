#include "camera.h"
#include "gtc/matrix_transform.hpp"

Camera::Camera(Renderer* renderer, ProjectionType type) : Entity(renderer){
	_view = glm::mat4(1.0f);
	setProjection(type);
}

Camera::~Camera() {

}

void Camera::setView(glm::vec3 direction, glm::vec3 up) {
	_view = glm::lookAt(glm::vec3(transform.position), direction, up);
}

void Camera::setProjection(ProjectionType type) {
	_type = type;
	switch (_type)
	{
	case ProjectionType::orthographic:
		_proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f);
		break;
	case ProjectionType::perspective:
		_proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.01f, 100.0f);
		break;
	default:
		break;
	}

}

glm::mat4 Camera::getView() {
	return _view;
}

glm::mat4 Camera::getProjection() {
	return _proj;
}

void Camera::draw(Shader& shader) {
	_renderer->drawCamera(shader, getModel(), getView(), getProjection());
}