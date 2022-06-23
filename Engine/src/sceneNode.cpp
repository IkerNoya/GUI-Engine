#include "sceneNode.h"

SceneNode::SceneNode(Renderer* renderer, Shader& shader, const char* name) : Entity(renderer)
{
	_name = name;   
}

SceneNode::~SceneNode()
{
}
