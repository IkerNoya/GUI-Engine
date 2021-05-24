#ifndef GAME_H
#define GAME_H
#include "gamebase.h"

class Game : public Gamebase{

public:
	Game();
	~Game();
	void init() override;
	void update() override;
	void unload() override;
};

#endif // !GAME_H

