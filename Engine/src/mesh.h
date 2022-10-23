#ifndef MESH_H
#define MESH_H

#include "entity.h"
#include "export.h"
#include "glm.hpp"

#include <iostream>
#include <vector>
#include "Math/AABB.h"
#include "debug.h"

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
	glm::vec3 _minCollConst;
	glm::vec3 _minColl;
	glm::vec3 _maxCollConst;
	glm::vec3 _maxColl;

	glm::vec3 _minCollTotal;
	glm::vec3 _maxCollTotal;

	void setupMesh();
public:
	std::vector<Vertex>	vertices;
	std::vector<glm::vec3> aabbPositions;
	std::vector<unsigned int>	indices;
	std::vector<Texture> textures;
	class aiNode* node;

	Mesh();
	Mesh(Renderer* renderer, Shader& shader, std::vector<Vertex>	vertices, std::vector<unsigned int>	indices, std::vector<Texture> textures, const char* name);
	~Mesh();
	void Draw(Line* line);
	void SetMinColl(glm::vec3 value);
	void SetMaxColl(glm::vec3 value);
	glm::vec3 GetMinCollTotal();
	glm::vec3 GetMaxCollTotal();
	glm::vec3 GetMinColl();
	glm::vec3 GetMaxColl();

	void SetMinCollGeneral(glm::vec3 value);
	void SetMaxCollGeneral(glm::vec3 value);
	glm::vec3 GetMinCollGeneral();
	glm::vec3 GetMaxCollGeneral();
	void SetGeneralColls(Mesh* mesh);
	void TryChangeParentGeneralColls(Mesh* mesh);
	void TryChangeParentGeneralCollsWhenYouAreParent(Mesh* mesh);

	void UpdateColliderScale();
	void UpdateColliderPos();

	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;
	virtual void setColor(float r, float g, float b) override;
	void setNode(aiNode* newNode);
	inline aiNode* getNode() const { return node; }
};


#endif // !MESH_H


