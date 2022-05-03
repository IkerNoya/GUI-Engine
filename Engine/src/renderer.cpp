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
    createAtribPointers(attribute, 3, 6, 0);
}

void Renderer::setTintAttribPointer(unsigned int shaderID, const char* attribName) {
    unsigned int attribute = glGetAttribLocation(shaderID, attribName);
    createAtribPointers(attribute, 3, 6, 3);
}

void Renderer::setTexAttribPointer(unsigned int shaderID) {
    unsigned int posAttrib = glGetAttribLocation(shaderID, "pos");
    unsigned int colorAttrib = glGetAttribLocation(shaderID, "texColor");
    unsigned int texAttrib = glGetAttribLocation(shaderID, "aTexCoord");
    glUniform1i((glGetUniformLocation(shaderID, "ourTexture")), 0);
    createAtribPointers(posAttrib, 3, 9, 0);
    createAtribPointers(colorAttrib, 4, 9, 3);
    createAtribPointers(texAttrib, 2, 9, 7);
}

void Renderer::setCubeAttribPointer(unsigned int shaderID)
{
    unsigned int posAttrib = glGetAttribLocation(shaderID, "inPosition");
    unsigned int colorAttrib = glGetAttribLocation(shaderID, "inColor");
    unsigned int normalAttrib = glGetAttribLocation(shaderID, "inNormal");
    unsigned int texAttrib = glGetAttribLocation(shaderID, "inTexCoord");
    glUniform1i((glGetUniformLocation(shaderID, "ourTexture")), 0);
    createAtribPointers(posAttrib, 3, 11, 0);
    createAtribPointers(colorAttrib, 3, 11, 3);
    createAtribPointers(normalAttrib, 3, 11, 6);
    createAtribPointers(texAttrib, 2, 11, 9);
}

void Renderer::startProgram(Shader& shader, glm::mat4 model) {
	shader.useProgram();
    shader.setMat4("transform", model);
}

void Renderer::generateVAO(unsigned int& vao) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Renderer::generateVBO(unsigned int& vbo){
    glGenBuffers(1, &vbo);
}


void Renderer::bindVAO(unsigned int& vao) {
    glBindVertexArray(vao);
}

void Renderer::bindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
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
void Renderer::drawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model){
    bindVAO(vao);
    bindVBO(vbo, vertices, verticesAmmount);
    setTexAttribPointer(shader.getID());
    startProgram(shader, model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbindBuffers();
}
void Renderer::drawCamera(Shader& shader, glm::mat4 model, glm::mat4 view, glm::mat4 proj) {
    shader.useProgram();
    shader.setMat4("transform", model);
    shader.setMat4("view", view);
    shader.setMat4("proj", proj);
}

void Renderer::drawCube(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model)
{
    bindVAO(vao);
    bindVBO(vbo, vertices, verticesAmmount);
    setCubeAttribPointer(shader.getID());
    startProgram(shader, model);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    unbindBuffers();
}
