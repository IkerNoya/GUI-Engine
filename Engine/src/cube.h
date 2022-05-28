#ifndef CUBE_H
#define CUBE_H
#include "entity.h"
#include "texture_importer.h"
#include "export.h"
#include "shader.h"
#include "materials.h"

class ENGINE_API Cube : public Entity {
	int _width;
	int _height;
	bool _transparency;
	bool _hasTexture = true;
	unsigned int _vao = 0;
	unsigned int _vbo = 0;
	unsigned int _ebo = 0;

	TextureImporter* _texImporter;
	Shader _shader;
	Material material;

	float vertices[264] = {
		0.5f,  0.5f, 0.5f,   1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	   -0.5f, -0.5f, 0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	   -0.5f,  0.5f, 0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

		 0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   0.0f, 1.0f
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
	Cube(Renderer* renderer, Shader& shader, std::string name);
	Cube(Renderer* renderer, Shader& shader, std::string name, bool transparency);
	Cube(Renderer* renderer, Shader& shader, std::string name, const char* path, bool transparency);
	Cube(Renderer* renderer);
	~Cube();

	void initWithBasicTexture();
	void init(const char* diffuseTexturePath, const char* specularTexturePath);

	void loadSprite(const char* path);
	void loadSprite();

	void SetColor(float r, float g, float b);
	void SetColor(glm::vec3 color);

	void draw();

	void setTransparency(bool value);
	void ShouldHaveTextures(bool value);

	inline int getWidth() { return _width; }
	inline int getHeight() { return _width; }
	inline const char* getPath() { return _texImporter ? _texImporter->GetPath() : "No path has been added"; }


	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;

	virtual void setColor(float r, float g, float b) override;

};


#endif // !CUBE_H

