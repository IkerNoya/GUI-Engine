#ifndef SCENE_NODE_H
#define SCENE_NODE_H
#define SCENE_NODE_H
#include "export.h"
#include "entity.h"
#include <vector>

class Mesh;
class Renderer;
class Shader;

class ENGINE_API SceneNode : public Entity {
	std::vector<Mesh*> meshes;

public:
	SceneNode(Renderer* renderer, Shader& shader,  const char* name);
	~SceneNode();

};

#endif // !SCENE_NODE_H

