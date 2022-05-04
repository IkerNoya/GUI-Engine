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
	SpotLight, DirectionalLight, PointLight, AmbientLight 
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

	void loadBaseSprite();

public:
	LightSource(Renderer* renderer, Shader& shader, LightType type, std::string name);
	~LightSource();

	void init();
	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	void draw();

	inline glm::vec3 getColor() const { return _color; }

};



#endif // !LIGHT_SOURCE_H


