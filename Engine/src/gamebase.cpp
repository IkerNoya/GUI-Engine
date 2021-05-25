#include "GL/glew.h"

#include "gamebase.h"
#include <iostream>

#include "GLFW/glfw3.h"

Gamebase::Gamebase() {
	window = new Window(1280, 720);
	renderer = new Renderer();
    _vao = 0;
    _vbo = 0;
    _ebo = 0;
}

Gamebase::~Gamebase() {
	if (window) delete window;
	if (renderer) delete renderer;
}

int Gamebase::initEngine() {
    window->createWindow("Engine v0.1");
    glewInit();
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in GLEW INIT" << std::endl;
        std::cout << glewGetErrorString(glewInit()) << std::endl;
        return 0;
    }

    glGetIntegerv(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, nullptr);
    std::cout << glGetString(GL_VERSION) << std::endl;
    basicShader.createShader("..//Engine//src//shaders//vertexShader.shader", "..//Engine//src//shaders//fragmentShader.shader");

    float vertices[] = {
    0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    //unsigned int VBO, VAO, EBO;
    renderer->generateVAO(_vao);
    renderer->bindVBO(_vbo, vertices, 24);
    renderer->bindEBO(_ebo, indices, 6);

    renderer->setPositionAttribPointer(basicShader.getID(), "pos");
    renderer->setTintAttribPointer(basicShader.getID(), "color");

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	return 0;
}

void Gamebase::updateEngine() {
    bool wireMode = false;
	while (!glfwWindowShouldClose(window->getWindow())) {
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer->startProgram(basicShader);
        renderer->bindVAO(_vao);
        if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && !wireMode) {
            renderer->activateWireframeMode();
            wireMode = true;
        }
        else if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && wireMode) {
            renderer->deactivateWireframeMode();
            wireMode = false;
        }
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		update();
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}

void Gamebase::unloadEngine() {
    renderer->deleteBuffers(_vao, _vbo, _ebo);
    glDeleteProgram(basicShader.getID());
	glfwTerminate();
}
