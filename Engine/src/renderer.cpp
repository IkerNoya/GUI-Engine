#include "GL/glew.h"
#include "renderer.h"

#include "GLFW/glfw3.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::createAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition) {
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE,sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}

void Renderer::setPositionAttribPointer(unsigned int shaderID, const char* attribName) {
    unsigned int attribute = glGetAttribLocation(shaderID, attribName);
    createAtribPointers(attribute, 3, 6, 0);
}

void Renderer::setTintAttribPointer(unsigned int shaderID, const char* attribName) {
    unsigned int attribute = glGetAttribLocation(shaderID, attribName);
    createAtribPointers(attribute, 3, 6, 3);
}

void Renderer::startProgram(Shader& shader) {
	shader.useProgram();
}

void Renderer::generateVAO(unsigned int& vao) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Renderer::bindVAO(unsigned int& vao) {
    glBindVertexArray(vao);
}

void Renderer::bindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}

void Renderer::bindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}

void Renderer::bindAllBuffersAtOnce(unsigned int &vbo, unsigned int &vao, unsigned int& ebo, float *vertex, unsigned int *indices, int verticesAmmount, int indicesAmmount) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * verticesAmmount, vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}

void Renderer::activateWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::deactivateWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::unbindBuffers(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::deleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}