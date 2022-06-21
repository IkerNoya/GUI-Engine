#include "world_data.h"

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
		if (!_dataManager->getLevelEntities()[i]->getParent()) {
			if (ImGui::TreeNode(_dataManager->getLevelEntities()[i]->GetName().c_str())) {
				_dataManager->setSelectedEntity(_dataManager->getLevelEntities()[i]);
				for (auto* child : _dataManager->getLevelEntities()[i]->getChildren()) {
					if (ImGui::TreeNode(child->GetName().c_str())) {
						_dataManager->setSelectedEntity(child);
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
}

