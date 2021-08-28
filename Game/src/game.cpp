#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
	newSpeed = speed;
}
	
Game::~Game() {
	if (square) delete square;
	if (square2) delete square2;
	if (sprite1) delete sprite1;
}

	//initialization of game variables
void Game::init() {
	square = new Shape(Type::tri, renderer, basicShader, "Triangle1");
	square2 = new Shape(Type::quad, renderer, basicShader,"Square2");
	sprite1 = new Sprite(true, "res/textures/granadeIcon.png", Type::quad, renderer, textureShader, "Sprite1");

	square->initShape();
	square->setPos(200, 200, 0);
	square->setScale(200, 200, 0.5f);

	square2->initShape();
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
	//input
	inputs();

	//update
	square->setColor(gui->getColor().x, gui->getColor().y, gui->getColor().z);

	timer += time.getDeltaTime();

	//draw
	square->draw();
	square2->draw();
	sprite1->drawSprite();
	
	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::inputs() {
	if (input.getKey(D)) {
		sprite1->setPos(sprite1->transform.position.x + (newSpeed * time.getDeltaTime()), sprite1->transform.position.y, sprite1->transform.position.z);
	}
	if (input.getKey(A)) {
		sprite1->setPos(sprite1->transform.position.x - (newSpeed * time.getDeltaTime()), sprite1->transform.position.y, sprite1->transform.position.z);
	}
	if (input.getKey(W)) {
		sprite1->setPos(sprite1->transform.position.x, sprite1->transform.position.y + (newSpeed * time.getDeltaTime()), sprite1->transform.position.z);
	}
	if (input.getKey(S)) {
		sprite1->setPos(sprite1->transform.position.x, sprite1->transform.position.y - (newSpeed * time.getDeltaTime()), sprite1->transform.position.z);
	}
	if (input.getKey(LEFT_SHIFT)) {
		newSpeed = speed * 2;
	}
	else {
		newSpeed = speed;
	}
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