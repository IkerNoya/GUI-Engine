#ifndef PLAYER_H
#define PLAYER_H

#include "model.h"

class Camera;
class Renderer;
class Shader;

class Player{
	Camera* _camera;
	Model* playerModel;
	bool _isFirstPerson = false;
	float xOffset;
	float yOffset;

public:
	Player(Camera* camera, Shader& shader, Renderer* renderer, float speed, bool firstPerson);
	~Player();
	void SetPosition(glm::vec3 pos);
	void MoveForward(float value);
	void MoveRight(float value);
	void LookRight(float value);
	void LookUp(float value);
	void SpectatorCameraInputs(float value);

	glm::vec3 movement;
};


#endif // !PLAYER_H


