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

		glm::vec3 rotation = _dataManager->getSelectedEntity()->transform.rotation;

		bool shouldDraw = _dataManager->getSelectedEntity()->ShouldDraw();

		ImGui::Text(_dataManager->getSelectedEntity()->GetName().c_str());
		ImGui::Separator();
		ImGui::Checkbox("Enable ", &shouldDraw);
		ImGui::Separator();
		ImGui::Text("Transform");
		ImGui::DragFloat3("Position ", (float*)&_dataManager->getSelectedEntity()->transform.position, _entityPositionSpeed, -100,100);
		ImGui::Separator();
		ImGui::Text("Rotation");
		ImGui::DragFloat3("rotation ", (float*)&rotation, _entityRotationSpeed, -360, 360);
		ImGui::Separator();
		ImGui::Text("Scale");
		ImGui::DragFloat3("scale ", (float*)&_dataManager->getSelectedEntity()->transform.scale, _entityScaleSpeed, 0.1f, 100);
		ImGui::Separator();

		_dataManager->getSelectedEntity()->SetXRot(rotation.x);
		_dataManager->getSelectedEntity()->SetYRot(rotation.y);
		_dataManager->getSelectedEntity()->SetZRot(rotation.z);

		_dataManager->getSelectedEntity()->Hide(shouldDraw);

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