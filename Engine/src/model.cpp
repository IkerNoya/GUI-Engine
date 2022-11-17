#include "model.h"
#include "shader.h"
#include "renderer.h"
#include "texture_importer.h"
#include "dataManager.h"


Model::Model(Renderer* renderer, Shader& shader, const char* name) {
	_renderer = renderer;
	_shader = shader;
	_name = name;

	_dataManager = DataManager::Get();
	_dataManager->addEntity(this, _id);
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

	if (!texturesLoaded.empty()) {
		texturesLoaded.clear();
	}
	//Assimp::DefaultLogger::kill();
}

void Model::draw(Line* line)
{
	updateSelfAndChild();
	updateVectors();
	meshes.front()->SetGeneralColls(meshes[1]);
	if (!ShouldDraw())
		return;

	if (!meshes.empty()) {
		for (auto* mesh : meshes) {
			if (mesh)
				mesh->Draw(line);
		}
	}

}

void Model::setColor(glm::vec3 color)
{
}

void Model::setColor(float r, float g, float b)
{
}

void Model::AddMesh(Mesh* mesh) {
	if (mesh) {
		meshes.push_back(mesh);
	}
}
void Model::AddParentMesh(Mesh* mesh) {
	if (mesh) {
		parentMeshes.push_back(mesh);
	}
}