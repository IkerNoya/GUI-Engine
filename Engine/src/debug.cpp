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

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, &_vbo);

	//glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

}


void Line::draw(glm::vec3 pos1, glm::vec3 pos2,  glm::vec3 color) {
	updateVectors();
	updateMatrices();
	vertices = {
		pos1.x, pos1.y, pos1.z,
		pos2.x, pos2.y, pos2.z
	};
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	transform.position = pos1;
	_shader.setMat4("transform", getModelMatrix());
	lineColor = color;
	glUseProgram(_shader.getID());
	_shader.setVec3("outColor", lineColor);
	_shader.setVec3("PointA", pos1);
	_shader.setVec3("PointB", pos2);
	_shader.setFloat("thickness", 15.f);
	_shader.setFloat("marker_radius", 50.f);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void Line::setColor(glm::vec3 color) {
	
}

