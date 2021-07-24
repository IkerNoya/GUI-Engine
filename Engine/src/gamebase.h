#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "export.h"
#include "window.h"
#include "renderer.h"
#include "shape.h"
#include "sprite.h"
#include "shader.h"
#include "guiLayer.h"
#include "inspector.h"
#include "worldData.h"
#include "input.h"
#include "camera.h"
#include "dataManager.h"
#include "time_manager.h"
#include "vld.h"


class ENGINE_API Gamebase {

	Inspector* inspector;
	WorldData* worldData;
protected:
	Window* window;
	Renderer* renderer;
	DataManager* dataManager;
	Shader basicShader;
	Shader textureShader;
	Camera* camera;
	GuiLayer* gui;

	Input input;
	Time time;

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

