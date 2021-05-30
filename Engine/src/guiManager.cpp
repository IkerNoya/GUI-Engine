#include "guiManager.h"
#include "GLFW/glfw3.h"

GuiManager::GuiManager(Window* window) {
	_window = window;
	_width = 100.0f;
	_height = 100.0f;
	_buttonPressed = false;
}
GuiManager::~GuiManager() {}

void GuiManager::createTestWindow(const char* windowName){
	ImGui::Text(windowName);                           // Display some text (you can use a format string too)
	float f1;
	float f2;
	ImGui::SliderFloat("SHAPE A X", &f1, 0, 1280);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("SHAPE B X", &f2, 0, 1280);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::ColorEdit3("ColorPicker", (float*)&_color); // Edit 3 floats representing a color

	if (ImGui::Button("WIREFRAME"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		_buttonPressed = !_buttonPressed;

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}

void GuiManager::init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}


	ImGui_ImplGlfw_InitForOpenGL(_window->getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void GuiManager::begin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GuiManager::onRender() {
	/*createTestWindow("BRUH MOMENT");*/
	static bool showDemo = true;
	ImGui::ShowDemoWindow(&showDemo);
}

void GuiManager::end() {
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(_window->getWidth(), _window->getHeight());

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

}

void GuiManager::unload() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool GuiManager::getButtonPressed() {
	return _buttonPressed;
}

ImVec4 GuiManager::getColor() {
	return _color;
}
