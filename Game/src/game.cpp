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
	square->setPos(0, 0, 0);
	square->setScale(0.5f, 0.5f, 0.5f);
}

	//game update
void Game::update() {
	square->draw(basicShader);
	square->setPos(_x, 0, 0);
}

	// free memory
void Game::unload() {
	square->clearBuffers();
	if (square) delete square;
}