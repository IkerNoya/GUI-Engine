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
		quadVertices[4] = r; quadVertices[5] = r; quadVertices[6] = r;
		quadVertices[11] = r; quadVertices[12] = r; quadVertices[13] = r;
		quadVertices[18] = r; quadVertices[19] = r; quadVertices[20] = r;
		quadVertices[25] = r; quadVertices[26] = r; quadVertices[27] = r;
		break;
	case tri:
		triangleVertices[4] = r; triangleVertices[5] = r; triangleVertices[6] = r;
		triangleVertices[11] = r; triangleVertices[12] = r; triangleVertices[13] = r;
		triangleVertices[18] = r; triangleVertices[19] = r; triangleVertices[20] = r;
		break;
	default:
		break;
	}
}

void Shape::clearBuffers() {
	_renderer->deleteBuffers(_vao, _vbo, _ebo);
}

void Shape::draw(Shader& shader) {
	_renderer->draw(shader, _vao, getModel());
}

