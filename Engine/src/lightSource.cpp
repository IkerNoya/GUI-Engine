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

void LightSource::bindBuffers()
{
	_renderer->generateVAO(_vao);
	_renderer->generateVBO(_vbo);
	_renderer->bindVAO(_vao);
	_renderer->bindVBO(_vbo, vertices, 264);
	_renderer->bindEBO(_ebo, indices, 36);
}

LightSource::LightSource(Renderer* renderer, Shader& shader, LightType type, std::string name) : Entity(renderer)
{
	_renderer = renderer;
	_type = type;
	_name = name;
	_shader = shader;
	_texImporter = new TextureImporter();
	_isLightSource = true;
	_entityShader = shader;
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
	loadBaseSprite();
	_renderer->setCubeAttribPointer(_shader);
	bindBuffers();
}

void LightSource::setColor(glm::vec3 color)
{
	_color = color;
}

void LightSource::setColor(float r, float g, float b)
{
	_color = glm::vec3(r, g, b);
	_shader.setVec3("lightColor", r, g, b);
}

void LightSource::draw()
{
	updateMatrices();
	glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
	glActiveTexture(GL_TEXTURE0);
	_renderer->drawCube(_shader, _vao, _vbo, vertices, 264, GetModel());
	glDisable(GL_TEXTURE_2D);
}
