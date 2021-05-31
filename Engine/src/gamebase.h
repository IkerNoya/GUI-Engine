#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "export.h"
#include "window.h"
#include "renderer.h"
#include "shape.h"
#include "shader.h"
#include "guiLayer.h"
#include "input.h"
#include "camera.h"
#include "dataManager.h"
#include "vld.h"


class ENGINE_API Gamebase {

protected:
	Window* window;
	Renderer* renderer;
	DataManager* dataManager;
	Shader basicShader;
	GuiLayer* gui;
	Camera* camera;

	Input input;

	float _x1;
	float _x2;

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

