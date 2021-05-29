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
    _x1 = 0;
    _x2 = 0;
    view = glm::mat4(1.0f);
    proj = glm::mat4(1.0f);
}

Gamebase::~Gamebase() {
	if (window) delete window;
	if (renderer) delete renderer;
    if (gui) delete gui;
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
    
    view = glm::lookAt(glm::vec3(0,0,1.0f), glm::vec3(0, 0, -1.0f), glm::vec3(0, 1.0f, 0));
    proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f);
    //proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.01f, 100.0f);

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
        unsigned int viewLoc = glGetUniformLocation(basicShader.getID(), "view");
        unsigned int projLoc = glGetUniformLocation(basicShader.getID(), "proj");
        basicShader.useProgram();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


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
