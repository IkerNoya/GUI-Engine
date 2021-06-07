#include "inspector.h"
#include "GLFW/glfw3.h"

Inspector::Inspector(Window* window, DataManager* dataManager) : GuiLayer(window, dataManager) {
	_isWindowOpen = false;
	_posX = 0;
	_posY = 0;
	_posZ = 0;
}
Inspector::~Inspector() {

}
void Inspector::getEntity() {
	if (_dataManager) {
		_posX = _dataManager->getLevelEntities()[0]->transform.position.x;
		_posY = _dataManager->getLevelEntities()[0]->transform.position.y;
		_posZ = _dataManager->getLevelEntities()[0]->transform.position.z;
	}
}
void Inspector::createWindow() {
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Inspector", &_isWindowOpen)) {
		ImGui::End();
		return;
	}

	ImGui::Text("Transform");
	ImGui::Spacing();
	ImGui::SliderFloat("X", &_posX, 0.0f, 1920.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Y", &_posY, 0.0f, 1920.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Z", &_posZ, 0.0f, 1920.0f);
	ImGui::Spacing();
	ImGui::Text("Rotation");
	ImGui::Spacing();
	ImGui::Text("X");
	ImGui::SameLine();
	ImGui::Text("Y");
	ImGui::SameLine();
	ImGui::Text("Z");
	ImGui::Spacing();
	ImGui::Text("Scale");
	ImGui::Spacing();
	ImGui::Text("X");
	ImGui::SameLine();
	ImGui::Text("Y");
	ImGui::SameLine();
	ImGui::Text("Z");
	ImGui::Spacing();
	ImGui::End();
	_dataManager->getLevelEntities()[0]->setPos(_posX, _posY, _posZ);
}