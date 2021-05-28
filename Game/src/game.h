#ifndef GAME_H
#define GAME_H
#include "gamebase.h"

class Game : public Gamebase{
	Shape* square;
public:
	Game();
	~Game();
	void init() override;
	void update() override;
	void unload() override;
};

#endif // !GAME_H

