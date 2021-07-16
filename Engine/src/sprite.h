#ifndef SPRITE_H
#define SPRITE_H
#include "shape.h"
#include "texture_importer.h"
#include "export.h"

class ENGINE_API Sprite : public Shape {
	int _width;
	int _height;
	bool _transparency;

	TextureImporter* texImporter;

	float texQuadVertices[36] = {
		1.0f,  1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  0.0f, 0.0f,
	   -1.0f,  1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  0.0f, 1.0f
	};

	float texTriVertices[27] = {
		0.5f,-0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   1.0f,0.0f,
		0.0f, 0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   0.5f,1.0f,
	   -0.5f,-0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   0.0f,0.0f
	};
public:

	Sprite(bool transparency, Type type, Renderer* renderer, std::string name);
	Sprite(bool transparency, const char* path, Type type, Renderer* renderer, std::string name);
	Sprite(int width, int height, const char* path, bool transparency, Type type, Renderer* renderer, std::string name);
	~Sprite();

	void init(Shader& shader);

	void LoadSprite();
	void LoadSprite(int width, int height);
	void LoadSprite(int width, int height, const char* path);

	void bindTexture();
	void blendSprite();
	void unblendSprite();

	void drawSprite(Shader& shader);

	void setWidth(int width);
	int getWidth();
	void setHeight(int height);
	int getHeight();
	void setPath(const char* path);
	const char* getPath();
};

#endif // !SPRITE_H
