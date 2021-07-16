#ifndef SHAPE_H
#define SHAPE_H
#include "export.h"
#include "renderer.h"
#include "entity.h"


enum class ENGINE_API Type {
    quad, tri
};

class ENGINE_API Shape : public Entity{
protected:
    float quadVertices[28] = {
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f   // top left 
    };
    unsigned int quadIndices[6] = {
        0,1,3,
        1,2,3
    };
    float triangleVertices[21] = {
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
    };
    unsigned int triangleIndices[3] = {
        0, 1, 2
    };
    Type shape;

public:
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;

    Shape(Type type, Renderer* renderer, std::string name);
    ~Shape();

    void initShape(Shader& shader);

    void generateVAO();

    void bindVAO();
    void bindVBO();
    void bindEBO();

    void bindBuffers(float* quadVertex, float* triVertex, int quadVertexSize, int triVertexSize);

    void setColor(float r, float g, float b);

    void clearBuffers();


    void draw(Shader& shader);
};


#endif // !SHAPE_H

