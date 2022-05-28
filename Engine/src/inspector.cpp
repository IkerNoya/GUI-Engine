#include "inspector.h"
#include "GLFW/glfw3.h"
#include	"gtc/type_ptr.hpp"

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
//Cambiar todo a la mierda
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


		ImGui::Text(_dataManager->getSelectedEntity()->GetName().c_str());
		ImGui::Separator();
		ImGui::Text("Transform");
		ImGui::SliderFloat("X Position", &_posX, _posX -_entityPositionSpeed, _posX + _entityPositionSpeed);
		ImGui::SliderFloat("Y Position", &_posY, _posY  - _entityPositionSpeed, _posY + _entityPositionSpeed);
		ImGui::SliderFloat("Z Position", &_posZ, _posZ - _entityPositionSpeed, _posZ + _entityPositionSpeed);
		ImGui::Separator();
		ImGui::Text("Rotation");
		ImGui::SliderFloat("X Rotation", &_rotX, _rotX - _entityRotationSpeed, _rotX + _entityRotationSpeed);
		ImGui::SliderFloat("Y Rotation", &_rotY, _rotY - _entityRotationSpeed, _rotY + _entityRotationSpeed);
		ImGui::SliderFloat("Z Rotation", &_rotZ, _rotZ - _entityRotationSpeed, _rotZ + _entityRotationSpeed);
		ImGui::Separator();
		ImGui::Text("Scale");
		ImGui::SliderFloat("X Scale", &_scaleX, 0.0f, _scaleX + _entityScaleSpeed);
		ImGui::SliderFloat("Y Scale", &_scaleY, 0.0f, _scaleY + _entityScaleSpeed);
		ImGui::SliderFloat("Z Scale", &_scaleZ, 0.0f, _scaleZ + _entityScaleSpeed);
		ImGui::Separator();

		_dataManager->getSelectedEntity()->SetPosition(_posX, _posY, _posZ);

		_dataManager->getSelectedEntity()->SetXRot(_rotX);
		_dataManager->getSelectedEntity()->SetYRot(_rotY);
		_dataManager->getSelectedEntity()->SetZRot(_rotZ);

		_dataManager->getSelectedEntity()->SetScale(_scaleX, _scaleY, _scaleZ);

		if (_dataManager->getSelectedEntity()->IsLightSource()) {
			_color = _dataManager->getSelectedEntity()->getColor();
			ImGui::Text("Light");
			ImGui::SliderFloat("Intensity", &_lightIntensity, 0.0f, 1.f);
			ImGui::Separator();
			ImGui::ColorPicker3("color", glm::value_ptr(_color));
			_dataManager->getSelectedEntity()->GetShader().setFloat("specularStrength", _lightIntensity);
			_dataManager->getSelectedEntity()->setEntityColor(_color);
		}
	}
	ImGui::End();
}