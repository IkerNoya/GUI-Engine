#include "window.h"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

Window::Window() {
	
}

Window::~Window() {

}

void Window::createWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(800, 600, "Engine v0.1", NULL, NULL);
	if (_window == NULL) {
		std::cout << "ERROR - Window creation failed" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback); // allows window resize
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* Window::getWindow() {
	return _window;
}