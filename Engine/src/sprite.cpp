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

	uv[0].u = 0.0f; uv[0].v = 0.0f;
	uv[1].u = 0.0f; uv[1].v = 0;
	uv[2].u = 0;    uv[2].v = 0;
	uv[3].u = 0;    uv[3].v = 0.0f;


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

void Sprite::SetAnimation(Animation* anim){
	animation = anim;
	_previousFrame = std::numeric_limits<unsigned int>::max_digits10;
}

void Sprite::SetAnimationCoords(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3){
	 _vertices[7] = u0;  _vertices[8] = v0;
	_vertices[16] = u1; _vertices[17] = v1;
	_vertices[25] = u2; _vertices[26] = v2;
	_vertices[34] = u3; _vertices[35] = v3;
}

void Sprite::UpdateAnimation(Time& time){
	if (animation != NULL) {
		animation->Update(time);
		_currentFrame = animation->GetCurrentFrame();

		if (_currentFrame != _previousFrame) {
			SetAnimationCoords(animation->GetAnimation()[_currentFrame].frameCoords[0].u, animation->GetAnimation()[_currentFrame].frameCoords[0].v,
							   animation->GetAnimation()[_currentFrame].frameCoords[3].u, animation->GetAnimation()[_currentFrame].frameCoords[3].v, 
							   animation->GetAnimation()[_currentFrame].frameCoords[2].u, animation->GetAnimation()[_currentFrame].frameCoords[2].v, 
							   animation->GetAnimation()[_currentFrame].frameCoords[1].u, animation->GetAnimation()[_currentFrame].frameCoords[1].v);
			_previousFrame = _currentFrame;
		}
		SetAnimation(animation);
	}
}

void Sprite::SetCurrentAnimation(int index){
	if (animation != NULL) {
		animation->SetCurrentAnimation(index);
	}
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
	_renderer->generateVBO(_vbo);
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
	 _vertices[3] = r;  _vertices[4] = g;  _vertices[5] = b;
	_vertices[12] = r; _vertices[13] = g; _vertices[14] = b;
	_vertices[21] = r; _vertices[22] = g; _vertices[23] = b;
	_vertices[30] = r; _vertices[31] = g; _vertices[32] = b;
}

void Sprite::draw()
{
	updateMatrices();
	if (_transparency) {
		blendSprite();
		bindTexture();
		_renderer->drawSprite(_shader, _vao, _vbo, _vertices, 36, GetModel());
		unblendSprite();
		glDisable(GL_TEXTURE_2D);
	}
	else {
		bindTexture();
		_renderer->drawSprite(_shader, _vao, _vbo, _vertices, 36, GetModel());
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
