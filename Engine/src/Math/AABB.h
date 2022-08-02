#ifndef AABB_H
#define AABB_H
#include "../export.h"
#include"../entity.h"

class ENGINE_API AABB : public Entity{
	bool isOnFrustrum = true;
	float verticesData[88];

	std::vector<glm::vec3> verticesPositions;
	std::vector<glm::vec3> verticesColor;
	glm::vec3 returnPositions[8];
	glm::vec3 returnColor[8];
	unsigned int indices[36] = {
		0,1,2,2,3,0,
		4,5,6,6,7,4,
		4,0,1,1,5,4,
		7,3,0,0,4,7,
		7,6,2,2,3,7,
		6,2,1,1,5,6
	};
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	void updateVertices();
	float getMin(std::vector<float> values);
	float getMax(std::vector<float> values);
	void bindVertexArrays();

public:
	AABB(Renderer* renderer, Shader& shader);
	~AABB();

	void Create();


	glm::vec3* generateAABB_pos(std::vector<glm::vec3> values);
	glm::vec3* generateAABB_frustrumPerspective(std::vector<glm::vec3> values);
	glm::vec3* generateAABB_color();

	void attachToEntity(ModelMatrix model, Transform transformAttached);
	void updateModel(ModelMatrix model, Transform transformAttached);
	void setVerticesColliders(glm::vec3 values[8]);
	void setVerticesColliders(unsigned int index, glm::vec3 value);
	void draw(class Line* line);
};


#endif // !AABB_H

