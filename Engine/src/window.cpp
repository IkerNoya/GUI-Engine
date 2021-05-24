#include "window.h"

#include <iostream>

#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window() {
	_window = NULL;
}

Window::~Window() {

}

int Window::createWindow() {
	glfwInit();
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(800, 600, "Engine v0.1", NULL, NULL);
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