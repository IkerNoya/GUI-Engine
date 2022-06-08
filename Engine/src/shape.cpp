#include "shape.h"

#include <stdlib.h>

Shape::Shape(Type type, Renderer* renderer, Shader &shader, std::string name) : Entity(renderer){
	shape = type;
	_name = name;
	_shader = shader;

	_vao = 0;
	_vbo = 0;
	_ebo = 0;

	DataManager* data = DataManager::Get();

	data->addEntity(this, _id);
}
	
Shape::~Shape() {
	clearBuffers();
}

void Shape::initShape() {
	_renderer->setPositionAttribPointer(_shader.getID(), "pos");
	_renderer->setTintAttribPointer(_shader.getID(), "color");
	generateVAO();
	_renderer->generateVBO(_vbo);
	bindVBO();
	bindEBO();
}

void Shape::generateVAO() {
	_renderer->generateVAO(_vao);
}

void Shape::bindVAO() {
	_renderer->bindVAO(_vao);
}

void Shape::bindVBO() {
	switch (shape)
	{
	case Type::quad:
		_renderer->bindVBO(_vbo, quadVertices, 28);
		break;
	case Type::tri:
		_renderer->bindVBO(_vbo, triangleVertices, 22);
		break;
	default:
		break;
	}
}

void Shape::bindEBO() {
	switch (shape)
	{
	case Type::quad:
		_renderer->bindEBO(_ebo, quadIndices, 6);
		break;
	case Type::tri:
		_renderer->bindEBO(_ebo, triangleIndices, 3);
		break;
	default:
		break;
	}
}

void Shape::bindBuffers(float* quadVertex, float* triVertex, int quadVertexSize, int triVertexSize){
	generateVAO();
	_renderer->generateVBO(_vbo);
	switch (shape)
	{
	case Type::quad:
		_renderer->bindVBO(_vbo, quadVertex, quadVertexSize);
		_renderer->bindEBO(_ebo, quadIndices, 6);
		break;
	case Type::tri:
		_renderer->bindVBO(_vbo, triVertex, triVertexSize);
		_renderer->bindEBO(_ebo, triangleIndices, 3);
		break;
	default:
		break;
	}
}

void Shape::setColor(float r, float g, float b) {
	switch (shape)
	{
	case Type::quad:
		quadVertices[3] = r; quadVertices[4] = g; quadVertices[5] = b;
		quadVertices[9] = r; quadVertices[10] = g; quadVertices[11] = b;
		quadVertices[15] = r; quadVertices[16] = g; quadVertices[17] = b;
		quadVertices[21] = r; quadVertices[22] = g; quadVertices[23] = b;
		break;
	case Type::tri:
		triangleVertices[3] = r; triangleVertices[4] = g; triangleVertices[5] = b;
		triangleVertices[9] = r; triangleVertices[10] = g; triangleVertices[11] = b;
		triangleVertices[15] = r; triangleVertices[16] = g; triangleVertices[17] = b;
		break;
	default:
		break;
	}
}

void Shape::clearBuffers() {
	_renderer->deleteBuffers(_vao, _vbo, _ebo);
}

void Shape::draw() {
	updateMatrices();
	switch (shape)
	{
	case Type::quad:
		_renderer->draw(_shader, _vao, _vbo, quadVertices, 28, GetModelMatrix());
		break; 
	case Type::tri:
		_renderer->draw(_shader, _vao, _vbo, triangleVertices, 22, GetModelMatrix());
		break;
	default:
		break;
	}
}

