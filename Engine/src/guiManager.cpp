#include "guiManager.h"

GuiManager::GuiManager() {
	_width = 100.0f;
	_height = 100.0f;
	_buttonPressed = false;
}
GuiManager::~GuiManager() {}

void GuiManager::createTestWindow(const char* windowName, float& _x1, float& _x2){
	ImGui::Text(windowName);                           // Display some text (you can use a format string too)
	ImGui::SliderFloat("SHAPE A X", &_x1, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::SliderFloat("SHAPE B X", &_x2, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::ColorEdit3("ColorPicker", (float*)&_color); // Edit 3 floats representing a color

	if (ImGui::Button("WIREFRAME"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		_buttonPressed = !_buttonPressed;

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}

void GuiManager::init(GLFWwindow* window) {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window, true);
}

void GuiManager::setDarkStyle() {

	ImGui::StyleColorsDark();
}

void GuiManager::createFrame() {
	ImGui_ImplGlfwGL3_NewFrame();
}

void GuiManager::render() {
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::unload() {
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

bool GuiManager::getButtonPressed() {
	return _buttonPressed;
}

ImVec4 GuiManager::getColor() {
	return _color;
}