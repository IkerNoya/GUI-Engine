#include "model.h"
#include "shader.h"
#include "renderer.h"
#include "texture_importer.h"
#include "dataManager.h"
#include "sceneNode.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "assimp/Logger.hpp"
#include "assimp/LogStream.hpp"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogAux.h"

#include <filesystem>

#define FLIPPED_IMPORT_FLAGS (aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals)
#define IMPORT_FLAGS (aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals)

Model::Model(Renderer * renderer, Shader & shader, const char* path, bool shouldFlipUVs, const char* name) : Entity(renderer) {
	texImporter = new TextureImporter;
	_renderer = renderer;
	_shader = shader;
	_name = name;
	directory = "";

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
	
	LoadModel(path, shouldFlipUVs);
}

Model::~Model()
{
	if (!meshes.empty()) {
		for (auto* mesh : meshes) {
			if (mesh) {
				delete mesh;
				mesh = nullptr;
			}
		}
		meshes.clear();
	}

	if (_root) {
		delete _root;
		_root = nullptr;
	}

	if (!_rootChildren.empty()) {
		for (auto* child : _rootChildren) {
			if (child) {
				delete child;
				child = nullptr;
			}
		}
		_rootChildren.clear();
	}

	if (!texturesLoaded.empty()) {
		texturesLoaded.clear();
	}
	if (texImporter) {
		delete texImporter;
		texImporter = nullptr;
	}
	//Assimp::DefaultLogger::kill();
}

void Model::draw()
{
	updateSelfAndChild();
	updateVectors();
	if (!ShouldDraw())
		return;

	//for (unsigned int i = 0; i < meshes.size(); i++)
	//	meshes[i]->Draw(getModelMatrix());

	if (_root)
		_root->draw();
	if (!_rootChildren.empty())
		for (auto* node : _rootChildren)
			if (node)
				node->draw();

}

void Model::setColor(glm::vec3 color)
{
}

void Model::setColor(float r, float g, float b)
{
}

void Model::LoadModel(std::string path, bool shouldFlipUVs)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, shouldFlipUVs ? FLIPPED_IMPORT_FLAGS : IMPORT_FLAGS);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Error::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = std::filesystem::path(path).parent_path().string();
	if(scene)
		processNode(scene->mRootNode, scene, nullptr);

	std::cout << _rootChildren.size() << std::endl;

}

void Model::processNode(aiNode* node, const aiScene* scene, Entity* parent)
{
	SceneNode* thisNode = nullptr;
	if (parent == nullptr) {
		_root = new SceneNode(renderer, _shader, directory, node, scene, texturesLoaded);
		thisNode = _root;
		addChild(_root);
	}
	else {
		thisNode = new SceneNode(renderer, _shader, directory, node, scene, texturesLoaded);
		parent->addChild(thisNode);
		_rootChildren.push_back(thisNode);
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, thisNode);
	}
}