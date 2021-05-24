#ifndef WINDOW_H
#define WINDOW_H
#include "export.h"
struct GLFWwindow;
class ENGINE_API Window {
	GLFWwindow* _window;
public:
	Window();
	~Window();
	void createWindow();
	GLFWwindow* getWindow();
};
#endif // !WINDOW_H

