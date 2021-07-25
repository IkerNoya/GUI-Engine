#ifndef GAME_H
#define GAME_H
#include "gamebase.h"

class Game : public Gamebase{
	Shape* square;
	Shape* square2;
	Sprite* sprite1;
	float timer = 0;
	float speed = 300;
public:
	Game();
	~Game();
	void inputs();
	void init() override;
	void update() override;
	void unload() override;
};

#endif // !GAME_H

