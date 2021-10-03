#ifndef SPRITE_H
#define SPRITE_H
#include "entity.h"
#include "texture_importer.h"
#include "export.h"

class ENGINE_API Sprite : public Entity {
	int _width;
	int _height;
	bool _transparency;
	unsigned int _vao = 0;
	unsigned int _vbo = 0;
	unsigned int _ebo = 0;


	TextureImporter* texImporter;
	Shader _shader;

	float _vertices[32] = {
		1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  0.0f, 0.0f,
	   -1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  0.0f, 1.0f
	};

	unsigned int _indices[6] = {
		0,1,3,
		1,2,3
	};

	//float texTriVertices[27] = {
	//	0.5f,-0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   1.0f,0.0f,
	//	0.0f, 0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   0.5f,1.0f,
	//   -0.5f,-0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   0.0f,0.0f
	//};

	void generateVAO();
	void bindVAO();
	void bindVBO();
	void bindEBO();

	void bindBuffers();

	void bindTexture();
	void blendSprite();
	void unblendSprite();

	void clearBuffers();
public:

	Sprite(bool transparency, Renderer* renderer, Shader& shader, std::string name);
	Sprite(bool transparency, const char* path, Renderer* renderer, Shader& shader, std::string name);
	~Sprite();

	void init();

	void LoadSprite();
	void LoadSprite(int width, int height);
	void LoadSprite(int width, int height, const char* path);

	void draw();

	void setColor(float r, float g, float b);
	void setWidth(int width);
	int getWidth();
	void setHeight(int height);
	int getHeight();
	void setPath(const char* path);
	const char* getPath();
};

#endif // !SPRITE_H
