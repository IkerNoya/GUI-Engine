#include "GL/glew.h"

#include "gamebase.h"
#include <iostream>

#include "GLFW/glfw3.h"

#include "gui/imgui.h"
#include "gui/imgui_impl_glfw_gl3.h"

Gamebase::Gamebase() {
	window = new Window(1280, 720);
	renderer = new Renderer();
    _x = 0;
}

Gamebase::~Gamebase() {
	if (window) delete window;
	if (renderer) delete renderer;
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

    glGetIntegerv(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, nullptr);
    std::cout << glGetString(GL_VERSION) << std::endl;
    basicShader.createShader("..//Engine//src//shaders//vertexShader.shader", "..//Engine//src//shaders//fragmentShader.shader");

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(window->getWindow(), true);

    ImGui::StyleColorsDark();   

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

	return 0;
}

void Gamebase::updateEngine() {
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool wireMode = false;
	while (!glfwWindowShouldClose(window->getWindow())) {
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ImGui_ImplGlfwGL3_NewFrame();

		update();

        if (wireMode) {
            renderer->activateWireframeMode();
        }
        else{
            renderer->deactivateWireframeMode();
        }
        {
            ImGui::Text("Shape A");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("X Position", &_x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("WIREFRAME"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                wireMode = !wireMode;

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
         
	}
}

void Gamebase::unloadEngine() {
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glDeleteProgram(basicShader.getID());
	glfwTerminate();
}
