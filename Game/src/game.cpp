#include "game.h"

#pragma region xd
void Game::SetPos(Model* model)
{

	model->GetMeshes()[1]->SetPosition(0, 0.5, 0); // head

	model->GetMeshes()[2]->SetPosition(-0.040, 2.360, 0); // body
	model->GetMeshes()[2]->SetScale(0.5, 1.33, 0.5);

	model->GetMeshes()[3]->SetPosition(0, 1.385, 0); // hip
	model->GetMeshes()[3]->SetScale(1.500, 0.450, 1.400);

	model->GetMeshes()[4]->SetPosition(-0.570, 2.680, 0); // r leg
	model->GetMeshes()[4]->SetScale(0.33, 1.750, 0.33);

	model->GetMeshes()[6]->SetPosition(0.910, 2.680, 0); // left leg
	model->GetMeshes()[6]->SetScale(0.33, 1.750, 0.33);

	model->GetMeshes()[7]->SetPosition(-0.040, 0.840, -1.900); // left foot
	model->GetMeshes()[7]->SetScale(0.9, 0.200, 3);

	model->GetMeshes()[8]->SetPosition(3.960, 0, 0); // right arm
	model->GetMeshes()[8]->SetScale(3, 0.300, 0.5);

	model->GetMeshes()[9]->SetPosition(1.150, 0.0, 0); // r hand
	model->GetMeshes()[9]->SetScale(0.33, 2, 2);

	model->GetMeshes()[10]->SetPosition(-3.750, 0, 0); //l arm
	model->GetMeshes()[10]->SetScale(3, 0.300, 0.5);

	model->GetMeshes()[11]->SetPosition(-1.150, 0, 0); // l hand
	model->GetMeshes()[11]->SetScale(0.33, 2, 2);

	model->GetMeshes()[5]->SetScale(-0.040, 0.870, -1.950); // r foot
	model->GetMeshes()[5]->SetScale(0.9, 0.200, 3);

	model->SetPosition(0, 0, 2);
}
#pragma endregion xd 

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
	model = modelImporter->LoadModel("res/models/bodyna.fbx", false,"xd");
	model->SetPosition(-1, 1, 1);
	model->SetScale(0.1, 0.1, 0.1);
	model->transform.rotation = glm::vec3(180, 0, 0);
	//model = new Model(renderer, standardShader, "res/models/Mansion_Hall_Level.fbx", true,"mansion");
	//model = new Model(renderer, standardShader, "res/models/Bob.fbx", true,"Scene Graph Test");
	leftPlane = modelImporter->LoadModel("res/models/plane.fbx", false, "leftPlane");
	leftPlane->SetScale(0.1, 0.1, 0.05);
	leftPlane->SetPosition(1, 0, 2);
	leftPlane->transform.rotation = glm::vec3(0, -90, 0);
	downPlane = modelImporter->LoadModel("res/models/plane.fbx", false, "DownPlane");
	downPlane->SetScale(0.1, 0.1, 0.05);
	downPlane->SetPosition(0, -1, 2);
	downPlane->transform.rotation = glm::vec3(-90, 0, 0);
	backPlane = modelImporter->LoadModel("res/models/plane.fbx", false, "BackPlane");
	backPlane->SetScale(0.1, 0.1, 0.05);
	backPlane->SetPosition(0, 0, 3);
	backPlane->transform.rotation = glm::vec3(0, 180, 0);
	//bsp->addPlane(leftPlane,glm::vec3(0,-90,0), glm::vec3(0,90,0));
	//bsp->addPlane(downPlane, glm::vec3(-90, 0, 0), glm::vec3(90, 0, 0));
	//bsp->addPlane(backPlane, glm::vec3(0, 0, 0), glm::vec3(0, 180, 0));


	Scene = modelImporter->LoadScene("res/models/ScenePepe2.fbx", false);
	for (auto* sceneModel : Scene) {
		if (sceneModel) {
			sceneModel->SetScale(.1, .1, .1);
		}
	}
	dataManager->TryGetEntityFromPrefix("Plane_", planes);
	dataManager->TryGetEntityFromPrefix("Pepe", Pepes);
	//planes[0] = Pane3 = left | planes[1] = Plane2 = right | planes[2] = Plane1 = back 
	//bsp->addPlane((Model*)planes[0], glm::vec3(0, -90, 0), glm::vec3(0, 90, 0));
	//bsp->addPlane((Model*)planes[1], glm::vec3(0, 90, 0), glm::vec3(0, -90, 0));
	//bsp->addPlane((Model*)planes[2], glm::vec3(0, 0, 0), glm::vec3(0, 180, 0));
	bsp->addModelToCheck(model);
	//for (auto* xd : Pepes) {
	//	if (xd) {
	//		bsp->addModelToCheck((Model*)xd);
	//	}
	//}

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
	player->SetPosition(glm::vec3(camera->transform.position.x, camera->transform.position.y, camera->transform.position.z + 1));
	//player->SetPosition(cube->transform.position + glm::vec3(0, 0.5f, 0));

	//plane = Plane(glm::vec3(1,0,3), glm::vec3(1, 1, -1.f), glm::vec3(1, -1, -3));
	//std::cout << "debugging shader: " << DebuggingShader.getID();
	//plane.InitializeDebugLines(DebuggingShader, renderer);

	SetPos(model);
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
	bsp->checkPlaneCamera(camera);
	bsp->check();
	line->draw(spot->transform.position, point2->transform.position, glm::vec3(1, 0, 0));
	for (int i = 0; i < Scene.size(); i++) {
		if (Scene[i]) {
			Scene[i]->draw(line);
		}
	}
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
	if (modelImporter) {
		delete modelImporter;
		modelImporter = NULL;
	}
}

