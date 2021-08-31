#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "sprite.h"
#include "dataManager.h"

Sprite::Sprite(bool transparency, Renderer* renderer, Shader& shader, std::string name) : Entity(renderer)
{
	_transparency = transparency;
	texImporter = new TextureImporter();
	_shader = shader;
	_width = 0;
	_height = 0;
	_name = name;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

Sprite::Sprite(bool transparency, const char* path, Renderer* renderer, Shader& shader, std::string name) : Entity(renderer)
{
	_transparency = transparency;
	texImporter = new TextureImporter();
	texImporter->SetPath(path);
	_shader = shader;
	_name = name;


	_width = 0;
	_height = 0;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

Sprite::~Sprite()
{
	if (texImporter != NULL)
	{
		delete texImporter;
		texImporter = NULL;
	}
	clearBuffers();
}

void Sprite::init(){
	LoadSprite();
	_renderer->setTexAttribPointer(_shader.getID());
	bindBuffers();

}

void Sprite::LoadSprite() {
	if (texImporter)
		texImporter->LoadImage(_width, _height, _transparency);
	else
		std::cout << "Couldn't find image" << std::endl;

}

void Sprite::LoadSprite(int width, int height) {
	if (texImporter)
		texImporter->LoadImage(width, height, _transparency);
	else
		std::cout << "Couldn't find image" << std::endl;
}

void Sprite::LoadSprite(int width, int height, const char* path) {
	if (texImporter) {
		texImporter->SetPath(path);
		texImporter->LoadImage(width, height, _transparency);
	}
	else
		std::cout << "Couldn't find image" << std::endl;
}

void Sprite::generateVAO() {
	_renderer->generateVAO(_vao);
}
void Sprite::bindVAO(){
	_renderer->bindVAO(_vao);
}
void Sprite::bindVBO(){
	_renderer->bindVBO(_vbo, _vertices, 36);
}
void Sprite::bindEBO() {
	_renderer->bindEBO(_ebo, _indices, 6);
}

void Sprite::bindBuffers() {
	generateVAO();
	bindVAO();
	bindVBO();
	bindEBO();
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

void Sprite::clearBuffers() {
	_renderer->deleteBuffers(_vao, _vbo, _ebo);
}

void Sprite::setColor(float r, float g, float b) {
	 _vertices[4] = r;  _vertices[5] = g;  _vertices[6] = b;
	_vertices[13] = r; _vertices[14] = g; _vertices[15] = b;
	_vertices[22] = r; _vertices[23] = g; _vertices[24] = b;
	_vertices[31] = r; _vertices[32] = g; _vertices[33] = b;
}

void Sprite::draw()
{
	updateMatrices();
	if (_transparency) {
		blendSprite();
		bindTexture();
		_renderer->drawSprite(_shader, _vao, _vbo, _vertices, 36, getModel());
		unblendSprite();
		glDisable(GL_TEXTURE_2D);
	}
	else {
		bindTexture();
		_renderer->drawSprite(_shader, _vao, _vbo, _vertices, 36, getModel());
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
