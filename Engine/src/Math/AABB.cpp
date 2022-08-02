#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "AABB.h"
#include "../debug.h"

void AABB::updateVertices() {
	//cout << "VERTEX DATA POSITION" << endl;
	int i = 0;
	for (int j = 0; j < 8; j++) {
		if (i + 10 < 88) {
			verticesData[i] = verticesPositions[j].x;
			verticesData[i + 1] = verticesPositions[j].y;
			verticesData[i + 2] = verticesPositions[j].z;
			verticesData[i + 3] = verticesColor[j].x;
			verticesData[i + 4] = verticesColor[j].y;
			verticesData[i + 5] = verticesColor[j].z;
			verticesData[i + 6] = 0;
			verticesData[i + 7] = 0;
			verticesData[i + 8] = 0;
			verticesData[i + 9] = 0;
			verticesData[i + 10] = 0;
			i += 11;
		}
	}
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

void AABB::bindVertexArrays() {
	_entityShader.setAttribute("inPosition", 3, 11, 0);
	_entityShader.setAttribute("inColor", 3, 11, 3);
	_entityShader.setAttribute("inNormal", 3, 11, 6);
	_entityShader.setAttribute("inTexCoord", 2, 11, 9);
}

AABB::AABB(Renderer* renderer, Shader& shader) : Entity(renderer) {
	_entityShader = shader;
	for (int i = 0; i < 88; i++) {
		verticesData[i] = 0.0f;
	}
}

AABB::~AABB() {
}

void AABB::Create() {
	_renderer->generateVAO(vao);
	_renderer->bindVAO(vao);
	_renderer->generateVBO(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	bindVertexArrays();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

	float min_x = getMin(values_x);
	float max_x = getMax(values_x);
	float min_y = getMin(values_y);
	float max_y = getMax(values_y);
	float min_z = getMin(values_z);
	float max_z = getMax(values_z);

	std::vector<int> edges = { 0,1, 1,2, 2,3, 3,0, 4,5, 5,6, 6,7, 7,4, 1,5, 2,6, 3,7, 0,4 };

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

glm::vec3* AABB::generateAABB_color() {
	for (int i = 0; i < 8; i++) {
		returnColor[i] = glm::vec3(0, 1, 0);
	}
	return returnColor;
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
	verticesColor.resize(8);
	glm::vec3 colors = glm::vec3(0.f, 1.f, 0.f);

	for (int i = 0; i < 8; i++) {
			verticesPositions[i].x = values[i].x;
			verticesPositions[i].y = values[i].y;
			verticesPositions[i].z = values[i].z;

			verticesColor[i].x = colors.x;
			verticesColor[i].y = colors.y;
			verticesColor[i].z = colors.z;
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
	if (verticesPositions.size() <= 0 || !line) return;

	updateVertices();
	updateMatrices();
	_renderer->bindVAO(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	bindVertexArrays();
	_entityShader.useProgram();
	glDrawElements(GL_LINE_STRIP, 36, GL_UNSIGNED_INT, 0);
	_renderer->unbindBuffers();
}
