#include "window.h"

#include <iostream>

#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window() {
	_window = NULL;
	_width = 800;
	_height = 600;
}

Window::Window(int width, int height) {
	_window = NULL;
	_width = width;
	_height = height;
}

Window::~Window() {

}

int Window::createWindow(const char* name) {
	glfwInit();
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_width, _height, name, NULL, NULL);
	if (_window == NULL) {
		std::cout << "ERROR - Window creation failed" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback); // allows window resize
}

GLFWwindow* Window::getWindow() {
	return _window;
}

void Window::setWidth(int width) {
	_width = width;
}

int Window::getWidth() {
	return _width;
}

void Window::setHeight(int height) {
	_height = height;
}

int Window::getHeight() {
	return _height;
}
