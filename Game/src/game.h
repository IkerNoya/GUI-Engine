#ifndef GAME_H
#define GAME_H
#include "gamebase.h"

class Game : public Gamebase{
	Shape* triangle;
	Sprite* sprite1;
	Cube* cube;
	float timer = 0;
	float speed = 1;
	float rotationSpeed = 100;
		
	float lastX;
	float lastY;
	bool firstMouse = true;
	float xPosIn = 0;
	float yPosIn = 0;
public:
	Game();
	~Game();
	void Inputs();
	void Init() override;
	void Update() override;
	void Unload() override;
};

#endif // !GAME_H

