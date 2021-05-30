#include "GL/glew.h"

#include "gamebase.h"
#include <iostream>

#include "GLFW/glfw3.h"

#include "gtc/matrix_transform.hpp"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"


Gamebase::Gamebase() {
	window = new Window(1280, 720);
	renderer = new Renderer();
    gui = new GuiManager();
    camera = new Camera(renderer, ProjectionType::orthographic);
    _x1 = 0;
    _x2 = 0;
}

Gamebase::~Gamebase() {
	if (window) delete window;
	if (renderer) delete renderer;
    if (gui) delete gui;
    if (camera) delete camera;
}

int Gamebase::initEngine() {
    window->createWindow("Engine v0.1");
    glewExperimental = GL_TRUE;
    glewInit();
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in GLEW INIT" << std::endl;
        std::cout << glewGetErrorString(glewInit()) << std::endl;
        return 0;
    }
    glEnable(GL_DEPTH_TEST);
    glGetIntegerv(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, nullptr);
    std::cout << glGetString(GL_VERSION) << std::endl;
    input.setWindow(window->getWindow());
    basicShader.createShader("..//Engine//src//shaders//vertexShader.shader", "..//Engine//src//shaders//fragmentShader.shader");
    camera->setPos(0, 0, 1.0f);
    camera->setView(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));


    gui->init(window->getWindow());

    gui->setDarkStyle();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

	return 0;
}

void Gamebase::updateEngine() {
    bool show_demo_window = true;
    bool show_another_window = false;
    bool wireMode = false;
	while (!glfwWindowShouldClose(window->getWindow())) {
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gui->createFrame();

        camera->draw(basicShader);
      
		update();

        gui->createTestWindow("BOX", _x1, _x2);

        if (gui->getButtonPressed()) {
            renderer->activateWireframeMode();
        }
        else{
            renderer->deactivateWireframeMode();
        }
           
        gui->render();

		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
         
	}
}

void Gamebase::unloadEngine() {
    gui->unload();
    input.unloadWindow();
    glDeleteProgram(basicShader.getID());
	glfwTerminate();
}
