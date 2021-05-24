#include "GL/glew.h"

#include "gamebase.h"
#include <iostream>

#include "GLFW/glfw3.h"

Gamebase::Gamebase() {
	window = new Window();
}

Gamebase::~Gamebase() {
	if (window) delete window;
}

int Gamebase::initEngine() {
	window->createWindow();
	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in GLEW INIT" << std::endl;
		std::cout << glewGetErrorString(glewInit()) << std::endl;
		return 0;
	}

	glGetIntegerv(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, nullptr);
	std::cout << glGetString(GL_VERSION) << std::endl;
	return 0;
}

void Gamebase::updateEngine() {
	while (!glfwWindowShouldClose(window->getWindow())) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		update();
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}

void Gamebase::unloadEngine() {
	glfwTerminate();
}