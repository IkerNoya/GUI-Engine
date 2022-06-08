#include "model.h"
#include "shader.h"
#include "renderer.h"
#include "texture_importer.h"

ModelMat::ModelMat(Renderer * renderer, Shader & shader, char* path) : Entity(renderer) {
	texImporter = new TextureImporter;
	_renderer = renderer;
	_shader = shader;
	LoadModel(path);
}

void ModelMat::LoadModel(std::string path)
{
}

void ModelMat::processNode(aiNode* node, const aiScene* scene)
{
}

Mesh ModelMat::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> test;
	std::vector<unsigned int> test1;
	std::vector<Texture> test2;
	return Mesh(nullptr, _shader, test, test1, test2);
}

std::vector<Texture> ModelMat::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	return std::vector<Texture>();
}
