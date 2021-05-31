#include "game.h"


Game::Game() : Gamebase(){
	square = new Shape(Type::quad, renderer);
	dataManager->addEntity(square);
	square2 = new Shape(Type::quad, renderer);
	dataManager->addEntity(square2);
	dataManager->loadEntities();
}

Game::~Game() {
	if (square) delete square;
	if (square2) delete square2;
}

	//initialization of game variables
void Game::init() {
	square->initShape(basicShader);
	square->setPos(200, 200, 0);
	_x1 = 200;
	square->setScale(200, 200, 0.5f);
	square2->initShape(basicShader);
	square2->setPos(300, 500, 0);
	_x2 = 300;
	square2->setScale(200, 200, 0.5f);
	square2->setColor(0.0f, 0.0f, 1.0f);
}

	//game update
void Game::update() {
	square->draw(basicShader);
	square2->draw(basicShader);
	square->setPos(_x1, 200, 0);
	square->setColor(gui->getColor().x, gui->getColor().y, gui->getColor().z);
	square2->setPos(_x2, 400, 0);
}

	// free memory
void Game::unload() {
	square->clearBuffers();
	square2->clearBuffers();
	dataManager->clearLevelEntities();
	if (square) {
		delete square;
		square = NULL;
	}
	if (square2) {
		delete square2;
		square2 = NULL;
	}
}