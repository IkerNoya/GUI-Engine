#ifndef AABB_H
#define AABB_H
#include "../export.h"
#include"../entity.h"

class ENGINE_API AABB : public Entity{
	bool isOnFrustrum = true;
	float verticesData[56];
	std::vector<glm::vec3> verticesPositions;
	glm::vec3 returnPositions[8];
	glm::vec4 returnColor[8];
	void updateVertices();
	float getMin(std::vector<float> values);
	float getMax(std::vector<float> values);

public:
	AABB();
	~AABB();

	glm::vec3* generateAABB_pos(std::vector<glm::vec3> values);
	glm::vec3* generateAABB_frustrumPerspective(std::vector<glm::vec3> values);

	void attachToEntity(ModelMatrix model, Transform transformAttached);
	void updateModel(ModelMatrix model, Transform transformAttached);
	void setVerticesColliders(glm::vec3 values[8]);
	void setVerticesColliders(unsigned int index, glm::vec3 value);
	void draw(class Line* line);
};


#endif // !AABB_H

