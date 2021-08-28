#ifndef GAME_H
#define GAME_H
#include "gamebase.h"

class Game : public Gamebase{
	Shape* triangle;
	Shape* square2;
	Sprite* sprite1;
	float timer = 0;
	float speed = 300;
	float newSpeed;
public:
	Game();
	~Game();
	void inputs();
	void init() override;
	void update() override;
	void unload() override;
};

#endif // !GAME_H

