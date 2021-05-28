#include "shape.h"

#include <stdlib.h>

Shape::Shape(Type type, Renderer* renderer) : Entity(Entity::_renderer){
	shape = type;

	_vao = 0;
	_vbo = 0;
	_ebo = 0;

}
	
Shape::~Shape() {
	clearBuffers();
	if (_renderer) delete _renderer;
	
}

void Shape::initShape(Shader& shader) {
	_renderer->setPositionAttribPointer(shader.getID(), "pos");
	_renderer->setTintAttribPointer(shader.getID(), "color");
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
	case quad:
		_renderer->bindVBO(_vbo, quadVertices, 24);
		break;
	case tri:
		_renderer->bindVBO(_vbo, triangleVertices, 18);
		break;
	default:
		break;
	}
}

void Shape::bindEBO() {
	switch (shape)
	{
	case quad:
		_renderer->bindEBO(_ebo, quadIndices, 6);
		break;
	case tri:
		_renderer->bindEBO(_ebo, triangleIndices, 3);
		break;
	default:
		break;
	}
}

void Shape::draw(Shader& shader) {
	_renderer->draw(shader, _vao);
}

void Shape::clearBuffers() {
	_renderer->deleteBuffers(_vao, _vbo, _ebo);
}