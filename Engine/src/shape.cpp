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
		_renderer->bindVBO(_vbo, quadVertices, 28);
		break;
	case tri:
		_renderer->bindVBO(_vbo, triangleVertices, 22);
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

void Shape::setColor(float r, float g, float b) {
	switch (shape)
	{
	case quad:
		quadVertices[4] = r; quadVertices[5] = g; quadVertices[6] = b;
		quadVertices[11] = r; quadVertices[12] = g; quadVertices[13] = b;
		quadVertices[18] = r; quadVertices[19] = g; quadVertices[20] = b;
		quadVertices[25] = r; quadVertices[26] = g; quadVertices[27] = b;
		break;
	case tri:
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

void Shape::draw(Shader& shader) {
	switch (shape)
	{
	case quad:
		_renderer->draw(shader, _vao, _vbo, quadVertices, 28, getModel());
		break; 
	case tri:
		_renderer->draw(shader, _vao, _vbo, triangleVertices, 22, getModel());
		break;
	default:
		break;
	}
}

