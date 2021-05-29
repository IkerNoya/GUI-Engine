#include "game.h"


Game::Game() : Gamebase(){
	square = new Shape(quad, renderer);
	square2 = new Shape(quad, renderer);
}

Game::~Game() {
	if (square) delete square;
	if (square2) delete square2;
}

	//initialization of game variables
void Game::init() {
	square->initShape(basicShader);
	square->setPos(0, 0, 0);
	square->setScale(0.5f, 0.5f, 0.5f);
	square2->initShape(basicShader);
	square2->setPos(0, 0, 0);
	square2->setScale(-0.5f, 0.5f, 0.5f);
	square2->setColor(0.0f, 0.0f, 1.0f);
}

	//game update
void Game::update() {
	square->draw(basicShader);
	square2->draw(basicShader);
	square->setPos(_x1, 0, 0);
	square->setColor(gui->getColor().x, gui->getColor().y, gui->getColor().z);
	square2->setPos(_x2, 0, 0);
}

	// free memory
void Game::unload() {
	square->clearBuffers();
	square2->clearBuffers();
	if (square) {
		delete square;
		square = NULL;
	}
	if (square2) {
		delete square2;
		square2 = NULL;
	}
}