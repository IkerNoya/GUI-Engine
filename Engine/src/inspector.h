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
	float _scaleZ	;
	
public: 
	bool _isWindowOpen;
	Inspector(Window* window, DataManager* dataManager);
	~Inspector();
	void getEntity();
	virtual void createWindow() override;
};

#endif // !INSPECTOR_H


