#ifndef MESH_H
#define MESH_H

#include "entity.h"
#include "export.h"
#include "glm.hpp"

#include <iostream>
#include <vector>

class Shader;
class Renderer;

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texCoords;
};
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};
class ENGINE_API Mesh : public Entity
{
	unsigned int vao, vbo, ebo;
	Shader shader;
	Renderer* _renderer;
	void setupMesh();
public:
	std::vector<Vertex>	vertices;
	std::vector<unsigned int>	indices;
	std::vector<Texture> textures;
	Mesh(Renderer* renderer, Shader& shader, std::vector<Vertex>	vertices, std::vector<unsigned int>	indices, std::vector<Texture> textures);
	~Mesh();
	void Draw(glm::mat4 modelMat);

	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;
	virtual void setColor(float r, float g, float b) override;
};


#endif // !MESH_H


