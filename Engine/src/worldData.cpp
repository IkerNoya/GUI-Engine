#include "worldData.h"

WorldData::WorldData(Window* window, DataManager* dataManager) : GuiLayer(window, dataManager) {
	_isWindowOpen = true;

}
WorldData::~WorldData() {

}

void WorldData::createWindow() {
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("World Data", &_isWindowOpen)) {
		ImGui::End();
		return;
	}
	for (int i = 0; i < _dataManager->getLevelEntities().size(); i++) {
		if (ImGui::Button(_dataManager->getLevelEntities()[i]->getName().c_str(), ImVec2(ImGui::GetWindowWidth(), 50))) {
			_dataManager->setSelectedEntity(_dataManager->getLevelEntities()[i]);
		}
		ImGui::Spacing();
	}
	ImGui::End();
}

