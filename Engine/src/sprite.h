#ifndef SPRITE_H
#define SPRITE_H
#include "shape.h"
#include "export.h"

class ENGINE_API Sprite : public Shape {

	float quadTexVertices[32] = {
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f   // top left 
	};
	float triTexVertices[24] = {
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
	};

public:

	Sprite(Type type, Renderer* renderer, std::string name);
	~Sprite();

};

#endif // !SPRITE_H
