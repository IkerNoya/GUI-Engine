#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
}
	
Game::~Game() {
	if (cube) delete cube;
	if (cube2) delete cube2;
	if (cube3) delete cube3;
	if (spot) delete spot;
	if (point) delete point;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;

	cube = new Cube(renderer, standardShader, "cube");
	cube->init("res/textures/container2.png", "res/textures/container2_specular.png");
	cube->SetPosition(0, .5f, -1.f);
	cube->SetScale(.25f, .25f, .25f);

	cube2 = new Cube(renderer, standardShader, "cube2");
	cube2->init("res/textures/container2.png", "res/textures/container2_specular.png");
	cube2->SetPosition(0, 1, -1.f);
	cube2->SetScale(.25f, .25f, .25f);

	cube3 = new Cube(renderer, standardShader, "cube3");
	cube3->init("res/textures/container2.png", "res/textures/container2_specular.png");
	cube3->SetPosition(0, -1, -1.f);
	cube3->SetScale(.25f, .25f, .25f);

	spot = new LightSource(renderer, standardShader, LightType::SpotLight, "spot");
	spot->init();
	spot->SetPosition(.5f, .5f, -1.f);
	spot->SetYRot(-90);
	spot->SetScale(.1f, .1f, .1f);
	spot->setColor(.5f, .5f, .5f);

	point = new LightSource(renderer, standardShader, LightType::PointLight, "point");
	point->init();
	point->SetPosition(-.5f, .5f, -1.f);
	point->SetYRot(-90);
	point->SetScale(.1f, .1f, .1f);
	point->setColor(.5f, .5f, .5f);
}

	//game update
void Game::Update() {
	//input
	Inputs();


	timer += time.getDeltaTime();

	//draw
	point->draw();
	spot->draw();
	cube->draw();
	cube2->draw();
	cube3->draw();
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
	if (cube2) {
		delete cube2;
		cube2 = NULL;
	}
	if (cube3) {
		delete cube3;
		cube3 = NULL;
	}
	if (spot) {
		delete spot;
		spot = NULL;
	}
	if (point) {
		delete point;
		point = NULL;
	}
}

