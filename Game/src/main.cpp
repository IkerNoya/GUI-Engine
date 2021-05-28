#include "game.h"
#include <iostream>

int main() {
	Game* game = new Game();
	if (game != NULL) {
		game->initEngine();
		game->init();
		game->updateEngine();
		game->unload();
		game->unloadEngine();
		delete game;
	}
	return 0;
}