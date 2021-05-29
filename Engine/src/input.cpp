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

void Input::unloadWindow() {
	if (_window) _window = NULL;
}