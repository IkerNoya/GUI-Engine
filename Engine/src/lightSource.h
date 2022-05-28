#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H
#include "export.h"
#include <glm.hpp>
#include <iostream>
#include "entity.h"


class Renderer;
class TextureImporter;
class Shader; 

enum class LightType {
	SpotLight, DirectionalLight, PointLight 
};
class ENGINE_API LightSource : public Entity
{
	LightType _type;
	Renderer* _renderer;
	TextureImporter* _texImporter;
	Shader _shader;
	glm::vec3 _color;
	unsigned int _vbo = 0;
	unsigned int _vao = 0;
	unsigned int _ebo = 0;

	unsigned int diffuse;
	unsigned int specular;

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

	void loadBaseSprite();
	void bindBuffers();

public:
	LightSource(Renderer* renderer, Shader& shader, LightType type, std::string name);
	~LightSource();

	void init();
	virtual void setColor(glm::vec3 color) override;
	virtual void setColor(float r, float g, float b) override;

	void draw();

	inline virtual glm::vec3 getColor() const override { return _color; std::cout << "Hola"; }

};



#endif // !LIGHT_SOURCE_H


