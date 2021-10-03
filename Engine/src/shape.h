#ifndef SHAPE_H
#define SHAPE_H
#include "export.h"
#include "renderer.h"
#include "entity.h"
#include "dataManager.h"


enum class ENGINE_API Type {
    quad, tri
};

class ENGINE_API Shape : public Entity{
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;

    float quadVertices[24] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f   // top left 
    };
    unsigned int quadIndices[6] = {
        0,1,3,
        1,2,3
    };
    float triangleVertices[18] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
    };
    unsigned int triangleIndices[3] = {
        0, 1, 2
    };

    Type shape;
    Shader _shader;

    void generateVAO();

    void bindVAO();
    void bindVBO();
    void bindEBO();

    void bindBuffers(float* quadVertex, float* triVertex, int quadVertexSize, int triVertexSize);

    void clearBuffers();

public:

    Shape(Type type, Renderer* renderer, Shader& shader, std::string name);
    ~Shape();

    void initShape();

    void setColor(float r, float g, float b);

    void draw();
};


#endif // !SHAPE_H

