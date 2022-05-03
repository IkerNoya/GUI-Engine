#include "cube.h"
#include "dataManager.h"
#include <GL/glew.h>

void Cube::generateVAO()
{
	_renderer->generateVAO(_vao);
}

void Cube::bindVAO()
{
	_renderer->bindVAO(_vao);
}

void Cube::bindVBO()
{
	_renderer->bindVBO(_vbo, vertices, 192);
}

void Cube::bindEBO()
{
	_renderer->bindEBO(_ebo, indices, 36);
}

void Cube::bindBuffers()
{
	generateVAO();
	_renderer->generateVBO(_vbo);
	bindVAO();
	bindVBO();
	bindEBO();
}

void Cube::bindTextures()
{
	glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
	glActiveTexture(GL_TEXTURE0);
}

void Cube::blendSprite()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Cube::unblendSprite()
{
	glDisable(GL_BLEND);
}

void Cube::clearBuffers()
{
	_renderer->deleteBuffers(_vao, _vbo, _ebo);
}

Cube::Cube(Renderer* renderer, Shader& shader, std::string name, bool transparency) : Entity(renderer)
{
	_transparency = transparency;
	_texImporter = new TextureImporter();
	_shader = shader;
	_width = 0;
	_height = 0;
	_name = name;
	
	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

Cube::Cube(Renderer* renderer, Shader& shader, std::string name, const char* path, bool transparency) : Entity(renderer)
{
	_transparency = transparency;
	_texImporter = new TextureImporter();
	_texImporter->SetPath(path);
	_shader = shader;
	_width = 0;
	_height = 0;
	_name = name;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

Cube::Cube(Renderer* renderer) : Entity(renderer)
{
	_transparency = false;
	_texImporter = new TextureImporter();
	_width = 0;
	_height = 0;
	_name = "cube_" + _id;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

Cube::~Cube()
{
	if (_texImporter) {
		delete _texImporter;
		_texImporter = nullptr;
	}
}

void Cube::init()
{
	loadSprite();
	_renderer->setCubeAttribPointer(_shader.getID());
	bindBuffers();
}

void Cube::loadSprite(const char* path)
{
	if (_texImporter){
		_texImporter->SetPath(path);
		_texImporter->LoadImage(_width, _height, _transparency);
	}
	else
		std::cout << "Couldn't find image" << std::endl;
}

void Cube::loadSprite()
{
	if (_texImporter)
		_texImporter->LoadImage(_width, _height, _transparency);
	else
		std::cout << "Couldn't find image" << std::endl;
}

void Cube::draw()
{
	updateMatrices();
	if (_transparency) {
		blendSprite();
		bindTextures();
		_renderer->drawCube(_shader, _vao, _vbo, vertices, 192, GetModel());
		unblendSprite();
		glDisable(GL_TEXTURE_2D);
	}
	else {
		bindTextures();
		_renderer->drawCube(_shader, _vao, _vbo, vertices, 192, GetModel());
		glDisable(GL_TEXTURE_2D);
	}
}
