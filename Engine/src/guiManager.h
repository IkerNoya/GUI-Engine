#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "export.h"
#include "gui/imgui.h"
#include "gui/imgui_impl_glfw.h"
#include "gui/imgui_impl_opengl3.h"
#include "window.h"


class ENGINE_API GuiManager {
	int _width;
	int _height;
	bool _buttonPressed;
	ImVec4 _color;
	Window* _window;
public:
	GuiManager(Window* window);
	~GuiManager();
	void init();
	void createTestWindow(const char* windowName);
	void unload();
	bool getButtonPressed();
	void begin();
	void onRender();
	void end();
	ImVec4 getColor();
};
#endif // !GUIMANAGER_H

