#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
	square = new Shape(Type::tri, renderer, "Triangle1");
	square2 = new Shape(Type::quad, renderer, "Square2");
	sprite1 = new Sprite(false, "res/textures/meme1.jpg", Type::quad, renderer, "Sprite1");
}

Game::~Game() {
	if (square) delete square;
	if (square2) delete square2;
	if (sprite1) delete sprite1;
}

	//initialization of game variables
void Game::init() {
	square->initShape(basicShader);
	square->setPos(200, 200, 0);
	square->setScale(200, 200, 0.5f);

	square2->initShape(basicShader);
	square2->setPos(300, 500, 0);
	square2->setScale(200, 200, 0.5f);
	square2->setColor(0.0f, 0.0f, 1.0f);

	sprite1->init(textureShader);
	sprite1->setPos(700, 100, 0);
	sprite1->setScale(200, 200, 0.5f);
	sprite1->setColor(1.0f, 1.0f, 1.0f);
	
}

	//game update
void Game::update() {
	square->setColor(gui->getColor().x, gui->getColor().y, gui->getColor().z);
	square->draw(basicShader);
	square2->draw(basicShader);
	sprite1->drawSprite(textureShader);
	std::cout << "timer: " << timer << "\n";
	timer += time.getDeltaTime();
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
	if (sprite1) {
		delete sprite1;
		sprite1 = NULL;
	}
}