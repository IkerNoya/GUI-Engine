#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
	newSpeed = speed;
}
	
Game::~Game() {
	if (triangle) delete triangle;
	if (square2) delete square2;
	if (sprite1) delete sprite1;
}

	//initialization of game variables
void Game::init() {
	triangle = new Shape(Type::tri, renderer, basicShader, "Triangle1");
	square2 = new Shape(Type::quad, renderer, basicShader,"Square2");
	sprite1 = new Sprite(true, "res/textures/granadeIcon.png", renderer, textureShader, "Sprite1");

	triangle->initShape();
	triangle->setPos(200, 200, 0);
	triangle->setScale(200, 200, 0.5f);
	square2->setColor(0.0f, 1.0f, 1.0f);

	square2->initShape();
	square2->setPos(300, 500, 0);
	square2->setScale(200, 200, 0.5f);
	square2->setColor(0.0f, 0.0f, 1.0f);

	sprite1->init();
	sprite1->setPos(700, 100, 0);
	sprite1->setScale(200, 200, 0.5f);
	sprite1->setColor(1.0f, 1.0f, 1.0f);
	
}

	//game update
void Game::update() {
	//input
	inputs();

	//update

	timer += time.getDeltaTime();

	//draw
	triangle->draw();
	square2->draw();
	sprite1->draw();
	
	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::inputs() {
	if (input.getKey(D)) {
		sprite1->transform.position.x +=time.getDeltaTime() * newSpeed;
	}
	if (input.getKey(A)) {
		sprite1->transform.position.x -= time.getDeltaTime() * newSpeed;
	}
	if (input.getKey(W)) {
		sprite1->transform.position.y += time.getDeltaTime() * newSpeed;
	}
	if (input.getKey(S)) {
		sprite1->transform.position.y -= time.getDeltaTime() * newSpeed;
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
	dataManager->clearLevelEntities();
	if (triangle) {
		delete triangle;
		triangle = NULL;
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