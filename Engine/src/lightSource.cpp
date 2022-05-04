#include <GL/glew.h>
#include "lightSource.h"
#include "renderer.h"
#include "dataManager.h"
#include "texture_importer.h"
#include "shader.h"


void LightSource::loadBaseSprite()
{
	float width = 0;
	float height = 0;
	if (_texImporter) {
		_texImporter->SetPath("../Engine/res/textures/BlankTexture.jpg");
		_texImporter->LoadImage(width, height, false);
	}
	else
		std::cout << "Couldn't find image" << std::endl;
}

LightSource::LightSource(Renderer* renderer, Shader& shader, LightType type, std::string name) : Entity(renderer)
{
	_renderer = renderer;
	_type = type;
	_name = name;
	_shader = shader;
	_texImporter = new TextureImporter();
	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

LightSource::~LightSource()
{
	if (_texImporter){
		delete _texImporter;
		_texImporter = nullptr;
	}
}

void LightSource::init()
{

}

void LightSource::setColor(glm::vec3 color)
{
	_color = color;
}

void LightSource::setColor(float r, float g, float b)
{
	_color = glm::vec3(r, g, b);
}

void LightSource::draw()
{
	_shader.setVec3("lightColor", _color);
}
