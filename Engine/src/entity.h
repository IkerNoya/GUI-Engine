#ifndef ENTITY_H
#define ENTITY_H
#include "export.h"
#include "renderer.h"
#include "mat4x4.hpp"
// using glm vec3 temporarily, will later use my own class

struct ENGINE_API Rotation {
	glm::mat4 x;
	glm::mat4 y;
	glm::mat4 z;
};

struct ENGINE_API Model {
	glm::mat4 translate;
	Rotation rotation;
	glm::mat4 scale;
	glm::mat4 trs;
};

struct ENGINE_API Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

//basic enitity for now
class ENGINE_API Entity {
protected:
	Renderer* _renderer;
	Model model;
	void updateModel();
public:
	Entity(Renderer* renderer);
	~Entity();
	Transform transform;
	Renderer* getRenderer();
	glm::mat4 getModel();
	void setPos(float x, float y, float z);
	void setXRot(float angle);
	void setYRot(float angle);
	void setZRot(float angle);
	void setScale(float x, float y, float z);
};

#endif // !ENTITY_H

