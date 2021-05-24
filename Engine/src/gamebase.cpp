#include "gamebase.h"
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

Gamebase::Gamebase() {
	window = new Window();
}

Gamebase::~Gamebase() {
	if (window) delete window;
}

int Gamebase::initEngine() {
	window->createWindow();
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit != GLEW_OK) {
		std::cout << "Error in GLEW INIT" << std::endl;
		return 0;
	}

	glGetIntegerv(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, nullptr);
	std::cout << glGetString(GL_VERSION) << std::endl;
	return 0;
}

void Gamebase::updateEngine() {
	while (!glfwWindowShouldClose(window->getWindow())) {

	}
}
