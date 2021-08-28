#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "input.h"

Input::Input() {
	_window = NULL;
}
Input::Input(GLFWwindow* window) {
	_window = window;
}
Input::~Input() {
	if (_window) _window = NULL;
}

void Input::setWindow(GLFWwindow* window) {
	_window = window;
}

bool Input::getKey(keyCode key) {
	return glfwGetKey(_window, key) == GLFW_PRESS;
}

bool Input::getKeyUp(keyCode key) {
	return glfwGetKey(_window, key) == GLFW_RELEASE;
}

bool Input::getMouseButton(MouseButtons mb) {
	return glfwGetMouseButton(_window, mb) == GLFW_PRESS;
}

bool Input::getMouseButtonUp(MouseButtons mb) {
	return glfwGetMouseButton(_window, mb) == GLFW_RELEASE;
}

glm::vec2 Input::getMousePosition2D() {
	double xPos, yPos;
	glfwGetCursorPos(_window, &xPos, &yPos);

	mousePosition = glm::vec3(xPos, yPos, 0.0f);

	return mousePosition;
}

glm::vec3 Input::getMousePosition3D() {
	double xPos, yPos, zPos;
	zPos = 0;
	glfwGetCursorPos(_window, &xPos, &yPos);

	mousePosition = glm::vec3(xPos, yPos, zPos);

	return mousePosition;
}

void Input::unloadWindow() {
	if (_window) _window = NULL;
}