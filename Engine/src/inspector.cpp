#include "inspector.h"
#include "GLFW/glfw3.h"

Inspector::Inspector(Window* window, DataManager* dataManager) : GuiLayer(window, dataManager) {
	_isWindowOpen = true;

	_posX = 0;
	_posY = 0;
	_posZ = 0;

	_rotX = 0;
	_rotY = 0;
	_rotZ = 0;

	_scaleX = 0;
	_scaleY = 0;
	_scaleZ = 0;
}
Inspector::~Inspector() {

}

void Inspector::getEntity() {
	if (_dataManager && _dataManager->getSelectedEntity()) {
		_posX = _dataManager->getSelectedEntity()->transform.position.x;
		_posY = _dataManager->getSelectedEntity()->transform.position.y;
		_posZ = _dataManager->getSelectedEntity()->transform.position.z;
	}
}
void Inspector::createWindow() {
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Inspector", &_isWindowOpen)) {
		ImGui::End();
		return;
	}

	if (_dataManager->getSelectedEntity() != NULL) {

		_posX = _dataManager->getSelectedEntity()->transform.position.x;
		_posY = _dataManager->getSelectedEntity()->transform.position.y;
		_posZ = _dataManager->getSelectedEntity()->transform.position.z;

		_rotX = _dataManager->getSelectedEntity()->transform.rotation.x;
		_rotY = _dataManager->getSelectedEntity()->transform.rotation.y;
		_rotZ = _dataManager->getSelectedEntity()->transform.rotation.z;

		_scaleX = _dataManager->getSelectedEntity()->transform.scale.x;
		_scaleY = _dataManager->getSelectedEntity()->transform.scale.y;
		_scaleZ = _dataManager->getSelectedEntity()->transform.scale.z;


		ImGui::Text(_dataManager->getSelectedEntity()->getName().c_str());
		ImGui::Spacing();
		ImGui::Text("Transform");
		ImGui::Spacing();
		ImGui::SliderFloat("X Position", &_posX, 0.0f, _window->getWidth());
		ImGui::Spacing();
		ImGui::SliderFloat("Y Position", &_posY, 0.0f, _window->getHeight());
		ImGui::Spacing();
		ImGui::SliderFloat("Z Position", &_posZ, -10.0f, 10.0f);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Rotation");
		ImGui::Spacing();
		ImGui::SliderFloat("X Rotation", &_rotX, -10.0f, 10.0f);
		ImGui::Spacing();						  
		ImGui::SliderFloat("Y Rotation", &_rotY, -10.0f, 10.0f);
		ImGui::Spacing();						  
		ImGui::SliderFloat("Z Rotation", &_rotZ, -10.0f, 10.0f);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Scale");
		ImGui::Spacing();
		ImGui::SliderFloat("X Scale", &_scaleX, 0.0f, _window->getWidth());
		ImGui::Spacing();
		ImGui::SliderFloat("Y Scale", &_scaleY, 0.0f, _window->getHeight());
		ImGui::Spacing();
		ImGui::SliderFloat("Z Scale", &_scaleZ, 0.0f, _window->getWidth());
		ImGui::Spacing();

		_dataManager->getSelectedEntity()->setPosition(_posX, _posY, _posZ);

		_dataManager->getSelectedEntity()->setXRot(_rotX);
		_dataManager->getSelectedEntity()->setYRot(_rotY);
		_dataManager->getSelectedEntity()->setZRot(_rotZ);

		_dataManager->getSelectedEntity()->setScale(_scaleX, _scaleY, _scaleZ);
	}
	ImGui::End();
}