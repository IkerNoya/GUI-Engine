#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
	newSpeed = speed;
}
	
Game::~Game() {
	if (triangle) delete triangle;
	if (square2) delete square2;
	if (sprite1) delete sprite1;
	if (player) delete player;
	if (idle) delete idle;
}

	//initialization of game variables
void Game::Init() {
	triangle = new Shape(Type::tri, renderer, basicShader, "Triangle1");
	square2 = new Shape(Type::quad, renderer, basicShader,"Square2");
	sprite1 = new Sprite(true, "res/textures/granadeIcon.png", renderer, textureShader, "Sprite1");
	player = new Sprite(true, "res/textures/PlayerShit.png", renderer, textureShader, "Player");

	triangle->initShape();
	triangle->SetPosition(200, 200, 0);
	triangle->SetScale(200, 200, 0.5f);
	square2->setColor(0.0f, 1.0f, 1.0f);

	square2->initShape();
	square2->SetPosition(300, 500, 0);
	square2->SetScale(200, 200, 0.5f);
	square2->setColor(0.0f, 0.0f, 1.0f);

	sprite1->init();
	sprite1->SetPosition(700, 100, 0);
	sprite1->SetScale(200, 200, 0.5f);
	sprite1->setColor(1.0f, 1.0f, 1.0f);


}

	//game update
void Game::Update() {
	//input
	Inputs();

	//update

	timer += time.getDeltaTime();

	//draw
	triangle->draw();
	square2->draw();
	sprite1->draw();
	
	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::Inputs() {
	// add inputs here
	if (input.getKey(keyCode::RIGHT)) {
		square2->transform.position.x += speed * time.getDeltaTime();
	}
	if (input.getKey(keyCode::LEFT)) {
		square2->transform.position.x -= speed * time.getDeltaTime();
	}
	if (input.getKey(keyCode::UP)) {
		square2->transform.position.y += speed * time.getDeltaTime();
	}
	if (input.getKey(keyCode::DOWN)) {
		square2->transform.position.y -= speed * time.getDeltaTime();
	}

	if (input.getKey(keyCode::D)) {
		triangle->transform.position.x += speed * time.getDeltaTime();
	}
	if (input.getKey(keyCode::A)) {
		triangle->transform.position.x -= speed * time.getDeltaTime();
	}
	if (input.getKey(keyCode::W)) {
		triangle->transform.position.y += speed * time.getDeltaTime();
	}
	if (input.getKey(keyCode::S)) {
		triangle->transform.position.y -= speed * time.getDeltaTime();
	}
}

	// free memory
void Game::Unload() {
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
	if (player){
		delete player;
		player = NULL;
	}
	if (idle) {
		delete idle;
		idle = NULL;
	}
}