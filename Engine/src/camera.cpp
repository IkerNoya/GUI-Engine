#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "gtc/matrix_transform.hpp"
#include "mat4x4.hpp"
#include "gtc/type_ptr.hpp"
#include "detail/type_mat4x4.hpp"
#include "dataManager.h"


Camera::Camera(Renderer* renderer, ProjectionType type) : Entity(renderer){
	_view = glm::mat4(1.0f);
	_proj = glm::mat4(1.0f);
	_name = "Camera";
	_type = type;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

Camera::~Camera() {

}

void Camera::setView(glm::vec3 position) {
	_view = glm::translate(glm::mat4(1.0), position);	
}

void Camera::setProjection(ProjectionType type) {
	_type = type;
	switch (_type)
	{
	case ProjectionType::orthographic:
		_proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f);
		break;
	case ProjectionType::perspective:
		_proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
		break;
	default:
		break;
	}

}

void Camera::init(Shader& shader) {
	unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
	unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
	unsigned int projLoc = glGetUniformLocation(shader.getID(), "proj");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(GetModel()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(getProjection()));
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
	updateMatrices();
	setView(glm::vec3(transform.position));
	setProjection(getProjectionType());

	_renderer->drawCamera(shader, GetModel(), getView(), getProjection());
}