#include "guiLayer.h"
#include "GLFW/glfw3.h"

GuiLayer::GuiLayer(Window* window, DataManager* dataManager) {
	_window = window;
	_isWorldDataOpen = false;

	_width = 100.0f;
	_height = 100.0f;
	_buttonPressed = false;
	_dataManager = dataManager;
}
GuiLayer::~GuiLayer() {}

void GuiLayer::createWindow() {
	//create window
}

void GuiLayer::init() {
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

void GuiLayer::createWorldData(const char* name, bool isActive) {
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(name, &isActive)) {
		ImGui::End();
		return;
	}

	ImGui::Text("ENTITY A");
	ImGui::Spacing();
	ImGui::Text("ENTITY B");
	ImGui::End();
}

void GuiLayer::begin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GuiLayer::onRender(bool &isInspectorOpen, bool &isWdOpen) {
	/*_isInspectorOpen = true;
	ImGui::ShowDemoWindow(&_isInspectorOpen);*/
	ImVec2 main_viewport_pos = ImGui::GetMainViewport()->Pos;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				_dataManager->saveEntities();
			}
			ImGui::EndMenu();
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::BeginMenu("Data"))
		{
			if (ImGui::MenuItem("Inspector"))
			{
				isInspectorOpen = !isInspectorOpen;
			}
			if (ImGui::MenuItem("World Entities"))
			{
				isWdOpen = !isWdOpen;
			}
			ImGui::EndMenu();
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::BeginMenu("Render Mode")) {
			if (ImGui::MenuItem("WireFrame")) {
				_wireframeMode = !_wireframeMode;
			}
			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
	}

}

void GuiLayer::end() {
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

void GuiLayer::unload() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool GuiLayer::getButtonPressed() {
	return _buttonPressed;
}

bool GuiLayer::getWireFrameMode() {
	return _wireframeMode;
}

ImVec4 GuiLayer::getColor() {
	return _color;
}

