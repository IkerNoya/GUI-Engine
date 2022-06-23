#ifndef WORLD_DATA_H
#define WORLD_DATA_H
#include "gui_layer.h"

class WorldData : public GuiLayer {

public: 
	bool _isWindowOpen = false;
	WorldData(Window* window, DataManager* dataManager);
	~WorldData();
	virtual void createWindow() override;
	void showChildren(Entity* entity);
};



#endif // !WORLD_DATA_H

