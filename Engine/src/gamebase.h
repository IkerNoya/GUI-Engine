#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "export.h"
#include "window.h"
#include "vld.h"

class Window;

class ENGINE_API Gamebase {
	Window* window;
public: 
	Gamebase();
	~Gamebase();
	int initEngine();
	void updateEngine();
	void unloadEngine();

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void unload() = 0;


};
#endif // !GAMEBASE_H

