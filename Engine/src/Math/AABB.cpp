#include "AABB.h"
#include "../debug.h"

void AABB::updateVertices() {
	//cout << "VERTEX DATA POSITION" << endl;
	int i = 0;
	for (int j = 0; j < 8; j++) {
		if (i + 2 < 56) {
			verticesData[i] = verticesPositions[j].x;
			verticesData[i + 1] = verticesPositions[j].y;
			verticesData[i + 2] = verticesPositions[j].z;
			i = i + 7;
		}
	}
	i = 0;
}

float AABB::getMin(std::vector<float> values) {
	if (values.size() <= 0)
		return -1;

	float min = values[0];

	for (int i = 0; i < values.size(); i++) {
		if (values[i] < min)
			min = values[i];
	}

	//cout << "min: " << min << endl;
	return min;
}

float AABB::getMax(std::vector<float> values) {
	if (values.size() <= 0)
		return -1;

	float max = values[0];

	for (int i = 0; i < values.size(); i++) {
		if (values[i] > max)
			max = values[i];
	}

	//cout << "max: " << min << endl;
	return max;
}

AABB::AABB() : Entity() {
	for (int i = 0; i < 56; i++) {
		verticesData[i] = 0.0f;
	}
}

AABB::~AABB() {
}

glm::vec3* AABB::generateAABB_pos(std::vector<glm::vec3> values) {
	if (values.size() <= 0)
		return nullptr;

	std::vector<float> values_x;
	std::vector<float> values_y;
	std::vector<float> values_z;

	for (int i = 0; i < values.size(); i++) {
		values_x.push_back(values[i].x);
		values_y.push_back(values[i].y);
		values_z.push_back(values[i].z);
	}

	float min_x = getMin(values_x) - 0.04f;
	float max_x = getMax(values_x) + 0.04f;
	float min_y = getMin(values_y) - 0.04f;
	float max_y = getMax(values_y) + 0.04f;
	float min_z = getMin(values_z) - 0.04f;
	float max_z = getMax(values_z) + 0.04f;

	returnPositions[0] = glm::vec3(min_x, max_y, min_z);
	returnPositions[1] = glm::vec3(min_x, min_y, min_z);
	returnPositions[2] = glm::vec3(max_x, min_y, min_z);
	returnPositions[3] = glm::vec3(max_x, max_y, min_z);
	returnPositions[4] = glm::vec3(min_x, max_y, max_z);
	returnPositions[5] = glm::vec3(min_x, min_y, max_z);
	returnPositions[6] = glm::vec3(max_x, min_y, max_z);
	returnPositions[7] = glm::vec3(max_x, max_y, max_z);

	return returnPositions;
}

glm::vec3* AABB::generateAABB_frustrumPerspective(std::vector<glm::vec3> values) {
	if (values.size() <= 0)
		return nullptr;

	std::vector<float> values_x;
	std::vector<float> values_y;
	std::vector<float> values_z;

	for (int i = 0; i < values.size(); i++) {
		values_x.push_back(values[i].x);
		values_y.push_back(values[i].y);
		values_z.push_back(values[i].z);
	}

	for (int i = 0; i < 8; i++) {
		returnPositions[i] = glm::vec3(values_x[i], values_y[i], values_z[i]);
	}
	return returnPositions;
}

void AABB::attachToEntity(ModelMatrix model, Transform transformAttached) {
	modelMatrix = model;
	transform = transformAttached;
	updateMatrices();
}

void AABB::updateModel(ModelMatrix model, Transform transformAttached) {
	modelMatrix = model;
	transform = transformAttached;
	updateMatrices();
}

void AABB::setVerticesColliders(glm::vec3 values[8]) {
	if (!values) 
		return;
	verticesPositions.resize(8);

	for (int i = 0; i < 8; i++) {
			verticesPositions[i].x = values[i].x;
			verticesPositions[i].y = values[i].y;
			verticesPositions[i].z = values[i].z;
	}

	updateVertices();
}

void AABB::setVerticesColliders(unsigned int index, glm::vec3 value) {
	if (index >= 8 || index < 0)
		return;

	verticesPositions[index] = value;

	updateVertices();
}

void AABB::draw(Line* line) {
	if (verticesPositions.size() <= 0) return;
	std::vector<int> edges = { 0,1, 1,2, 2,3, 3,0, 4,5, 5,6, 6,7, 7,4, 1,5, 2,6, 3,7, 0,4 };
	for (int i = 0; i < 24; i++) {
		if(line)
			if(i+1<24)
				line->draw(verticesPositions[edges[i]], verticesPositions[edges[i+1]], glm::vec3(0,1,0));
			else
				line->draw(verticesPositions[edges[i]], verticesPositions[edges[0]], glm::vec3(0,1,0));
	}
}
