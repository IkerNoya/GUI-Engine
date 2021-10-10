#ifndef SPRITE_H
#define SPRITE_H
#include "entity.h"
#include "texture_importer.h"
#include "export.h"
#include "animation.h"

struct UV {
	float u;
	float v;
};

class ENGINE_API Sprite : public Entity {
	int _width;
	int _height;
	int _previousFrame;
	int _currentFrame;
	bool _transparency;
	unsigned int _vao = 0;
	unsigned int _vbo = 0;
	unsigned int _ebo = 0;


	TextureImporter* texImporter;
	Shader _shader;
	Animation* animation;
	UV uv[4];

	//   Position                Color             UV
	float _vertices[36] = {
		1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,1.0f,  1, 1,
		1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,1.0f,  1, 0,
	   -1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,1.0f,  0, 0,
	   -1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,1.0f,  0, 1
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

	void SetAnimation(Animation* anim);
	void SetAnimationCoords(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3);
	void UpdateAnimation(Time& time);
	void SetCurrentAnimation(int index);

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
