#include "game.h"


Game::Game() : Gamebase(){
	square = new Shape(quad, renderer);
}

Game::~Game() {
	if (square) delete square;
}

	//initialization of game variables
void Game::init() {
	square->initShape(basicShader);
}

	//game update
void Game::update() {
	square->draw(basicShader);
}

	// free memory
void Game::unload() {
	square->clearBuffers();
	if (square) delete square;
}