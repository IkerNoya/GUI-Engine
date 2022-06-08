#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "gui_layer.h"

class Inspector : public GuiLayer {
	float _posX;
	float _posY;
	float _posZ;

	float _rotX;
	float _rotY;
	float _rotZ;

	float _scaleX;
	float _scaleY;
	float _scaleZ;

	float _lightIntensity = .3f;

	float _entityPositionSpeed = .1f;
	float _entityRotationSpeed = .5f;
	float _entityScaleSpeed = .05f;
	float _lightIntensitySpeed = .1f;

	bool _isEntityLightSource = false;
	
	glm::vec3 _color = glm::vec3(1);

public: 
	bool _isWindowOpen;
	Inspector(Window* window, DataManager* dataManager);
	~Inspector();
	void getEntity();
	virtual void createWindow() override;
};

#endif // !INSPECTOR_H


