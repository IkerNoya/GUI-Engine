#ifndef WINDOW_H
#define WINDOW_H
#include "export.h"

struct GLFWwindow;
class ENGINE_API Window {
	GLFWwindow* _window;
	int _width;
	int _height;
public:
	Window();
	Window(int width, int height);
	~Window();
	int createWindow(const char* name);
	GLFWwindow* getWindow();
	void setWidth(int width);
	int getWidth();
	void setHeight(int height);
	int getHeight();
};
#endif // !WINDOW_H

