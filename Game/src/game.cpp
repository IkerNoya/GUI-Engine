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
	if (player) delete player;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;

	cube = new Cube(renderer, standardShader, "cube");
	cube->init("res/textures/wood.png", "res/textures/wood.png");
	cube->SetPosition(0, -0.5f, -1.f);
	cube->SetScale(5, .1f, 5);

	//model = new Model(renderer, standardShader, "res/models/nanosuit/nanosuit.obj", false,"nanosuit");
	//model = new Model(renderer, standardShader, "res/models/vamp/dancing_vampire.dae", false,"vamp");
	//model = new Model(renderer, standardShader, "res/models/backpack/backpack.obj", true,"backpack");
	//model = new Model(renderer, standardShader, "res/models/claire/claire.obj", false,"claire");
	model = new Model(renderer, standardShader, "res/models/Pepe2.fbx", false,"xd");
	//model = new Model(renderer, standardShader, "res/models/Mansion_Hall_Level.fbx", true,"mansion");
	//model = new Model(renderer, standardShader, "res/models/Bob.fbx", true,"Scene Graph Test");
	leftPlane = new Model(renderer, standardShader, "res/models/plane.fbx", false, "leftPlane");
	leftPlane->SetScale(0.1, 0.1, 0.05);
	leftPlane->SetPosition(1, 0, 2);
	leftPlane->transform.rotation = glm::vec3(0, -90, 0);
	downPlane = new Model(renderer, standardShader, "res/models/plane.fbx", false, "leftPlane");
	downPlane->SetScale(0.1, 0.1, 0.05);
	downPlane->SetPosition(0, -1, 2);
	downPlane->transform.rotation = glm::vec3(-90, 0, 0);
	backPlane = new Model(renderer, standardShader, "res/models/plane.fbx", false, "leftPlane");
	backPlane->SetScale(0.1, 0.1, 0.05);
	backPlane->SetPosition(0, 0, 3);
	backPlane->transform.rotation = glm::vec3(0, 180, 0);
	bsp->addPlane(leftPlane,glm::vec3(0,-90,0), glm::vec3(0,90,0));
	bsp->addPlane(downPlane, glm::vec3(-90, 0, 0), glm::vec3(90, 0, 0));
	bsp->addPlane(backPlane, glm::vec3(0, 0, 0), glm::vec3(0, 180, 0));

	bsp->addModelToCheck(model);

	model->GetMeshes()[0]->SetGeneralColls(model->GetMeshes()[0]);
	for (int i = 0; i < model->GetMeshes().size(); i++) {
		std::cout << "mesh name: " << model->GetMeshes()[i]->GetName() << std::endl;
		std::cout << "min col x: " << model->GetMeshes()[i]->GetMinColl().x << " - y: " << model->GetMeshes()[i]->GetMinColl().y << " - z: " << model->GetMeshes()[i]->GetMinColl().z << std::endl;
		std::cout << "max col x: " << model->GetMeshes()[i]->GetMaxColl().x << " - y: " << model->GetMeshes()[i]->GetMaxColl().y << " - z: " << model->GetMeshes()[i]->GetMaxColl().z << std::endl;
		std::cout << std::endl;
		std::cout << "min col gen  x: " << model->GetMeshes()[i]->GetMinCollGeneral().x << " - y: " << model->GetMeshes()[i]->GetMinCollGeneral().y << " - z: " << model->GetMeshes()[i]->GetMinCollGeneral().z << std::endl;
		std::cout << "max col gen x: " << model->GetMeshes()[i]->GetMaxCollGeneral().x << " - y: " << model->GetMeshes()[i]->GetMaxCollGeneral().y << " - z: " << model->GetMeshes()[i]->GetMaxCollGeneral().z << std::endl;
		std::cout << std::endl;
		std::cout << " - - - - - - - - - - - - - - - - - - - - - - - - - " << std::endl;
		std::cout << std::endl;
	}
	//model->show(false);

	directional = new LightSource(renderer, standardShader, LightType::DirectionalLight, "directional");
	directional->init();
	directional->show(false);
	directional->SetPosition(.5f, .5f, -3.f);
	directional->transform.rotation.y = 90; 
	directional->transform.rotation.x = -45;
	directional->SetScale(.1f, .1f, .1f);
	directional->setColor(1, 1, 1);

	spot = new LightSource(renderer, standardShader, LightType::SpotLight, "spot");
	spot->init();
	spot->SetPosition(.5f, .5f, -1.f);
	spot->transform.rotation.y = 90;
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

	player = new Player(camera, standardShader, renderer, 0, true);
	//player->SetPosition(cube->transform.position + glm::vec3(0, 0.5f, 0));

	//plane = Plane(glm::vec3(1,0,3), glm::vec3(1, 1, -1.f), glm::vec3(1, -1, -3));
	//std::cout << "debugging shader: " << DebuggingShader.getID();
	//plane.InitializeDebugLines(DebuggingShader, renderer);

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
	model->GetMeshes()[0]->SetGeneralColls(model->GetMeshes()[0]);
	model->draw(line);
	cube->draw();
	leftPlane->draw(line);
	downPlane->draw(line);
	backPlane->draw(line);
	//bsp->checkPlaneCamera(camera);
	//bsp->check();
	//line->draw(spot->transform.position, point2->transform.position, glm::vec3(1, 0, 0));

	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::Inputs() {
	// add inputs here

	if (input.getKey(keyCode::W)) {
		player->MoveForward(speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::S)) {
		player->MoveForward(-speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::A)) {
		player->MoveRight(-speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::D)) {
		player->MoveRight(speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::RIGHT)) {
		player->LookRight(rotationSpeed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::LEFT)) {
		player->LookRight(-rotationSpeed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::UP)) {
		player->LookUp(rotationSpeed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::DOWN)) {
		player->LookUp(-rotationSpeed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::E)) {
		player->SpectatorCameraInputs(speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::Q)) {
		player->SpectatorCameraInputs(-speed * time.getDeltaTime());
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
	if (player) {
		delete player;
		player = NULL;
	}
}

