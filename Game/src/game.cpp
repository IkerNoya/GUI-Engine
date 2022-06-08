#include "game.h"

Game::Game() : Gamebase(){
}
	
Game::~Game() {
	if (cube) delete cube;
	if (model) delete model;
	if (directional) delete directional;
	if (spot) delete spot;
	if (point) delete point;
	if (point2) delete point2;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;

	cube = new Cube(renderer, standardShader, "cube");
	cube->init("res/textures/wood.png", "res/textures/wood.png");
	cube->SetPosition(0, -0.5f, -1.f);
	cube->SetScale(5, .1f, 5);

	model = new Model(renderer, standardShader, "res/models/backpack.obj");
	model->SetPosition(.5f, 1, -3.f);
	model->SetScale(.1f, .1f, .1f);
	model->setColor(1.0f,1.0f,1.0f);

	directional = new LightSource(renderer, standardShader, LightType::DirectionalLight, "directional");
	directional->init();
	directional->SetPosition(.5f, .5f, -3.f);
	directional->SetYRot(90);
	directional->SetXRot(-45);
	directional->SetScale(.1f, .1f, .1f);
	directional->setColor(1, 1, 1);

	spot = new LightSource(renderer, standardShader, LightType::SpotLight, "spot");
	spot->init();
	spot->SetPosition(.5f, .5f, -1.f);
	spot->SetYRot(90);
	spot->SetXRot(-45);
	spot->SetScale(.1f, .1f, .1f);
	spot->setColor(1, 1, 1);

	point = new LightSource(renderer, standardShader, LightType::PointLight, "point");
	point->init();
	point->SetPosition(1, .5f, -1.f);
	point->SetScale(.1f, .1f, .1f);
	point->setColor(1, 1, 1);

	point2 = new LightSource(renderer, standardShader, LightType::PointLight, "point2");
	point2->init();
	point2->SetPosition(-1, .5f, -1.f);
	point2->SetScale(.1f, .1f, .1f);
	point2->setColor(1, 1, 1);
}

	//game update
void Game::Update() {
	//input
	Inputs();


	timer += time.getDeltaTime();

	//draw
	directional->draw();
	spot->draw();
	point->draw();
	point2->draw();
	cube->draw();
	model->draw();
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
	if (model) {
		delete model;
		model = NULL;
	}
	if (directional) {
		delete directional;
		directional = NULL;
	}
	if (spot) {
		delete spot;
		spot = NULL;
	}
	if (point) {
		delete point;
		point = NULL;
	}
	if (point2) {
		delete point;
		point = NULL;
	}
}

