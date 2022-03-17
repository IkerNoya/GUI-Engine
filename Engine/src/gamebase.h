#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "export.h"
#include "window.h"
#include "renderer.h"
#include "shape.h"
#include "sprite.h"
#include "shader.h"
#include "gui_layer.h"
#include "inspector.h"
#include "world_data.h"
#include "input.h"
#include "camera.h"
#include "dataManager.h"
#include "time_manager.h"

class Renderer;
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
	int InitEngine();
	void UpdateEngine();
	void UnloadEngine();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Unload() = 0;

};
#endif // !GAMEBASE_H

