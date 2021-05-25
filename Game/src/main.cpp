#include "game.h"
#include <iostream>

int main() {
	Game* game = new Game();
	if (game != NULL) {
		game->initEngine();
		game->init();
		game->updateEngine();
		game->unloadEngine();
		game->unload();
		delete game;
	}
	return 0;
}