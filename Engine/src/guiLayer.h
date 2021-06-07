#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "export.h"
#include "gui/imgui.h"
#include "gui/imgui_impl_glfw.h"
#include "gui/imgui_impl_opengl3.h"
#include "window.h"
#include "dataManager.h"


class ENGINE_API GuiLayer {
	int _width;
	int _height;
	bool _buttonPressed;

	ImVec4 _color;

	bool _isWorldDataOpen;

protected:
	Window* _window;
	DataManager* _dataManager;

	virtual void createWindow();

public:
	GuiLayer(Window* window, DataManager* datamanager);
	~GuiLayer();
	void init();
	bool getButtonPressed();
	void createWorldData(const char* name, bool isActive);
	void begin();
	void onRender(bool& isInspectorOpen, bool& isWdOpen);
	void end();
	void unload();
	ImVec4 getColor();
};
#endif // !GUIMANAGER_H

