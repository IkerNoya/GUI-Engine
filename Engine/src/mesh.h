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
	glm::vec3 texCoords;
};
struct Texture {
	unsigned int id;
	std::string type;
};
class ENGINE_API Mesh : public Entity
{
	unsigned int vao, vbo, ebo;
	Shader shader;
	void setupMesh();
public:
	std::vector<Vertex>	vertices;
	std::vector<unsigned int>	indices;
	std::vector<Texture> textures;
	Mesh(Renderer* renderer, Shader& shader, std::vector<Vertex>	vertices, std::vector<unsigned int>	indices, std::vector<Texture> textures);
	~Mesh();
	void Draw();
};


#endif // !MESH_H


