#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "sprite.h"

Sprite::Sprite(bool transparency, Type type, Renderer* renderer, std::string name) : Shape(type, renderer, name)
{
	_transparency = transparency;
	texImporter = new TextureImporter();
}

Sprite::Sprite(bool transparency, const char* path, Type type, Renderer* renderer, std::string name) : Shape(type, renderer, name)
{
	_transparency = transparency;
	texImporter = new TextureImporter();
	texImporter->SetPath(path);
}

Sprite::Sprite(int width, int height, const char* path, bool transparency, Type type, Renderer* renderer, std::string name) : Shape(type, renderer, name)
{
	_transparency = transparency;
	texImporter = new TextureImporter(_width, _height, path, _transparency);
}

Sprite::~Sprite()
{
	if (texImporter != NULL)
	{
		delete texImporter;
		texImporter = NULL;
	}
}

void Sprite::init(Shader& shader){
	LoadSprite();
	_renderer->setTexAttribPointer(shader.getID());
	bindBuffers(texQuadVertices, texTriVertices, 36, 27);

}

void Sprite::LoadSprite() {
	if (texImporter)
		texImporter->LoadImage(_width, _height, _transparency);
	else
		std::cout << "Couldn't load image" << std::endl;

}

void Sprite::LoadSprite(int width, int height) {
	if (texImporter)
		texImporter->LoadImage(width, height, _transparency);
	else
		std::cout << "Couldn't load image" << std::endl;
}

void Sprite::LoadSprite(int width, int height, const char* path) {
	if (texImporter) {
		texImporter->SetPath(path);
		texImporter->LoadImage(width, height, _transparency);
	}
	else
		std::cout << "Couldn't load image" << std::endl;
}

void Sprite::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, texImporter->GetTexture());
	glActiveTexture(GL_TEXTURE0);
}

void Sprite::blendSprite(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Sprite::unblendSprite(){
	glDisable(GL_BLEND);
}

void Sprite::drawSprite(Shader& shader)
{
	if (_transparency) {
		blendSprite();
		bindTexture();
		switch (shape)
		{
			case Type::quad:
				_renderer->drawSprite(shader, _vao, _vbo, texQuadVertices, 36, getModel());
				break;			

			case Type::tri:
				_renderer->drawSprite(shader, _vao, _vbo, texTriVertices, 27, getModel());
				break;
		}
		unblendSprite();
		glDisable(GL_TEXTURE_2D);
	}
	else {
		bindTexture();
		switch (shape)
		{
		case Type::quad:
			_renderer->drawSprite(shader, _vao, _vbo, texQuadVertices, 36, getModel());
			//draw(shader);
			break;

		case Type::tri:
			_renderer->drawSprite(shader, _vao, _vbo, texTriVertices, 27, getModel());
			break;
		}
		glDisable(GL_TEXTURE_2D);
	}
}

void Sprite::setWidth(int width) {
	_width = width;
}

int Sprite::getWidth()
{
	return _width;
}

void Sprite::setHeight(int height) {
	_height = height;
}

int Sprite::getHeight() {
	return _height;
}

void Sprite::setPath(const char* path) {
	if (texImporter)
		texImporter->SetPath(path);
	else
		std::cout << "Couldn't set path" << std::endl;
}

const char* Sprite::getPath()
{
	if (texImporter)
		return texImporter->GetPath();
	else
		return nullptr;
}
