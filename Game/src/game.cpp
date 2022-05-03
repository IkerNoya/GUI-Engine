#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
}
	
Game::~Game() {
	if (cube) delete cube;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;

	cube = new Cube(renderer, standardShader, "cube");
	cube->init();
	cube->SetPosition(.75f, .5f, -1.f);
	cube->SetScale(.25f, .25f, .25f);
	cube->SetColor(1,1,1);
}

	//game update
void Game::Update() {
	//input
	Inputs();


	timer += time.getDeltaTime();

	//draw
	cube->draw();
	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::Inputs() {
	// add inputs here

	if (input.getKey(keyCode::W)) {
		camera->transform.position += camera->getForward() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::S)) {
		camera->transform.position -= camera->getForward() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::A)) {
		camera->transform.position -= camera->getRight() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::D)) {
		camera->transform.position += camera->getRight() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::Q)) {
		camera->transform.position -= camera->getUp() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::E)) {
		camera->transform.position += camera->getUp() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::RIGHT)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotateYaw(camera->rotationSpeed);
	}
	if (input.getKey(keyCode::LEFT)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotateYaw(-camera->rotationSpeed);
	}
	if (input.getKey(keyCode::UP)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotatePitch(camera->rotationSpeed);
	}
	if (input.getKey(keyCode::DOWN)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotatePitch(-camera->rotationSpeed);
	}
}

	// free memory
void Game::Unload() {
	dataManager->clearLevelEntities();
	if (cube) {
		delete cube;
		cube = NULL;
	}
}

