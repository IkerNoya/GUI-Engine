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
    dataManager = DataManager::Get();
    gui = new GuiLayer(window, dataManager);
    inspector = new Inspector(window, dataManager);
    worldData = new WorldData(window, dataManager);
    camera = new Camera(renderer, ProjectionType::perspective);
}

Gamebase::~Gamebase() {
	if (window) delete window;
	if (renderer) delete renderer;
    if (dataManager) delete dataManager;
    if (inspector) delete inspector;
    if (worldData) delete worldData;
    if (gui) delete gui;
    if (camera) delete camera;
}

int Gamebase::InitEngine() {
    window->createWindow("Engine v0.1");
    glewExperimental = GL_TRUE;
    glewInit();
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in GLEW INIT" << std::endl;
        std::cout << glewGetErrorString(glewInit()) << std::endl;
        return 0;
    }
    glGetIntegerv(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, nullptr);
    std::cout << glGetString(GL_VERSION) << std::endl;
    input.setWindow(window->getWindow());

    basicShader.createShader("..//Engine//src//shaders//vertexShader.vert", "..//Engine//src//shaders//fragmentShader.frag");
    textureShader.createShader("..//Engine//src//shaders//vertexShader.vert", "..//Engine//src//shaders//texFragmentShader.frag");

    glEnable(GL_DEPTH_TEST);


    camera->SetPosition(0, 0, -5.0f);
    //                     position                  
    camera->setView(camera->transform.position);
    camera->setProjection(camera->getProjectionType());

    camera->init(basicShader);
    camera->init(textureShader);

    gui->init();

    time.reset();


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

	return 0;
}

void Gamebase::UpdateEngine() {
    bool wireMode = false;
    inspector->getEntity();
	while (!window->windowShouldClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gui->begin();

        gui->onRender(inspector->_isWindowOpen, worldData->_isWindowOpen);

        if(inspector->_isWindowOpen)
            inspector->createWindow();

        if (worldData->_isWindowOpen)
            worldData->createWindow();

        camera->draw(basicShader);
        camera->draw(textureShader);
      
		Update();

        if (gui->getWireFrameMode()) {
            renderer->activateWireframeMode();
        }
        else{
            renderer->deactivateWireframeMode();
        }
           
        gui->end();
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();

        time.calculateFPS();
        time.tick();
	}
}

void Gamebase::UnloadEngine() {
    gui->unload();
    input.unloadWindow();
    glDeleteProgram(basicShader.getID());
	glfwTerminate();
}
