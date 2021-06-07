#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "guiLayer.h"

class Inspector : public GuiLayer {
	float _posX;
	float _posY;
	float _posZ;
	
public: 
	bool _isWindowOpen;
	Inspector(Window* window, DataManager* dataManager);
	~Inspector();
	void getEntity();
	virtual void createWindow() override;
};

#endif // !INSPECTOR_H


