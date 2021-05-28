#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "export.h"
#include "gui/imgui.h"
#include "gui/imgui_impl_glfw_gl3.h""

struct GLFWwindow;

class ENGINE_API GuiManager {
	int _width;
	int _height;
	bool _buttonPressed;
	ImVec4 _color;
public:
	GuiManager();
	~GuiManager();
	void init(GLFWwindow* window);
	void setDarkStyle();
	void createFrame();
	void createTestWindow(const char* windowName, float& _x);
	void render();
	void unload();
	bool getButtonPressed();
	ImVec4 getColor();
};
#endif // !GUIMANAGER_H

