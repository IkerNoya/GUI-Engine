#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"
#include "gtc/type_ptr.hpp"

#include "debug.h"

Line::Line() : Entity() {
	_vbo = 0;
	_vao = 0;
}

Line::Line(Shader& shader) : Entity() {
	_vbo = 0;
	_vao = 0;
	_shader = shader;

	Init();
}

Line::~Line() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

void Line::Init() {
	_renderer->generateVAO(_vao);
	_renderer->bindVAO(_vao);
	_renderer->generateVBO(_vbo);
}


void Line::draw(glm::vec3 pos1, glm::vec3 pos2,  glm::vec3 color) {
	updateVectors();
	updateMatrices();
	vertices = {
		pos1.x, pos1.y, pos1.z - 3,
		pos2.x, pos2.y, pos2.z - 3
	};
	transform.position = pos1;
	lineColor = color;
	_shader.setVec3("outColor", lineColor);
	_shader.setVec3("PointA", pos1);
	_shader.setVec3("PointB", pos2);
	_shader.setFloat("thickness", 15.f);
	_shader.setFloat("marker_radius", 50.f);
	_renderer->drawLines(_shader, _vao, _vbo, vertices.data(), vertices.size(), getModelMatrix());
}

void Line::setColor(glm::vec3 color) {
	
}

