#ifndef CUBE_H
#define CUBE_H
#include "entity.h"
#include "texture_importer.h"
#include "export.h"
#include "shader.h"

class ENGINE_API Cube : public Entity {
	int _width;
	int _height;
	bool _transparency;
	unsigned int _vao = 0;
	unsigned int _vbo = 0;
	unsigned int _ebo = 0;

	TextureImporter* _texImporter;
	Shader _shader;

	float vertices[216] = {
		0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 1.0f
	};

	unsigned int indices[36] = {
		0, 1, 3,
		1, 2, 3,
		4, 5, 7,
		5, 6, 7,
		8, 9, 11,
		9, 10, 11,
		12, 13, 15,
		13, 14, 15,
		16, 17, 19,
		17, 18, 19,
		20, 21, 23,
		21, 22, 23
	};

	void generateVAO();
	void bindVAO();
	void bindVBO();
	void bindEBO();

	void bindBuffers();

	void bindTextures();
	void blendSprite();
	void unblendSprite();

	void clearBuffers();

public:
	Cube(Renderer* renderer, Shader& shader, std::string name, bool transparency);
	Cube(Renderer* renderer, Shader& shader, std::string name, const char* path, bool transparency);
	Cube(Renderer* renderer);
	~Cube();

	void init();
	
	void loadSprite(const char* path);
	void loadSprite();

	void draw();

	inline int getWidth() { return _width; }
	inline int getHeight() { return _width; }
	inline const char* getPath() { return _texImporter ? _texImporter->GetPath() : "No path has been added"; }

};


#endif // !CUBE_H

