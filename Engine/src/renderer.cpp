#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"

#include "gtc/type_ptr.hpp"


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
    createAtribPointers(attribute, 4, 7, 0);
}

void Renderer::setTintAttribPointer(unsigned int shaderID, const char* attribName) {
    unsigned int attribute = glGetAttribLocation(shaderID, attribName);
    createAtribPointers(attribute, 3, 7, 4);
}

void Renderer::startProgram(Shader& shader, glm::mat4 model) {
    unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
	shader.useProgram();
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
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
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void Renderer::deleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Renderer::draw(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount,glm::mat4 model) {
    bindVAO(vao);
    bindVBO(vbo, vertices, verticesAmmount);
    setPositionAttribPointer(shader.getID(), "pos");
    setTintAttribPointer(shader.getID(), "color");
    startProgram(shader, model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbindBuffers();
}
void Renderer::drawCamera(Shader& shader, glm::mat4 model, glm::mat4 view, glm::mat4 proj) {
    unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
    unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
    unsigned int projLoc = glGetUniformLocation(shader.getID(), "proj");
    shader.useProgram();
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}
