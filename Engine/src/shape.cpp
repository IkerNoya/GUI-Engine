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
		quadVertices[4] = r; quadVertices[5] = g; quadVertices[6] = b;
		quadVertices[11] = r; quadVertices[12] = g; quadVertices[13] = b;
		quadVertices[18] = r; quadVertices[19] = g; quadVertices[20] = b;
		quadVertices[25] = r; quadVertices[26] = g; quadVertices[27] = b;
		break;
	case Type::tri:
		triangleVertices[4] = r; triangleVertices[5] = g; triangleVertices[6] = b;
		triangleVertices[11] = r; triangleVertices[12] = g; triangleVertices[13] = b;
		triangleVertices[18] = r; triangleVertices[19] = g; triangleVertices[20] = b;
		break;
	default:
		break;
	}
}

void Shape::clearBuffers() {
	_renderer->deleteBuffers(_vao, _vbo, _ebo);
}

void Shape::draw() {
	switch (shape)
	{
	case Type::quad:
		_renderer->draw(_shader, _vao, _vbo, quadVertices, 28, getModel());
		break; 
	case Type::tri:
		_renderer->draw(_shader, _vao, _vbo, triangleVertices, 22, getModel());
		break;
	default:
		break;
	}
}

