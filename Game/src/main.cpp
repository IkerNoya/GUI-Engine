#include "game.h"
#include <iostream>

int main() {
	Game* game = new Game();
	if (game != NULL) {
		game->InitEngine();
		game->Init();
		game->UpdateEngine();
		game->Unload();
		game->UnloadEngine();
		delete game;
	}
	return 0;
}