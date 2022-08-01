#include "model.h"
#include "shader.h"
#include "renderer.h"
#include "texture_importer.h"
#include "dataManager.h"

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

	_dataManager = DataManager::Get();
	_dataManager->addEntity(this, _id);
	
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

void Model::draw(Line* line)
{
	updateSelfAndChild();
	updateVectors();
	if (!ShouldDraw())
		return;

	//for (unsigned int i = 0; i < meshes.size(); i++)
	//	meshes[i]->Draw(getModelMatrix());

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
	Entity* thisNode = nullptr;

	if (parent == nullptr) {
		_root = new Entity(renderer);
		_root->SetName(node->mName.C_Str());
		
		thisNode = _root;
		addChild(_root);
	}
	else {
		thisNode = new Entity(renderer);
		thisNode->SetName(node->mName.C_Str());

		parent->addChild(thisNode);
		_rootChildren.push_back(thisNode);
	}
	_dataManager->addEntity(thisNode, thisNode->GetID());

	if (node->mNumMeshes > 0) {
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Mesh* newMesh = processMesh(mesh, scene);
			thisNode->addChild(newMesh);
			meshes.push_back(newMesh);
		}
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, thisNode);
	}
}
Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<glm::vec3> positions;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		glm::vec3 vec = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.position = vec;
		positions.push_back(vec);
		if (mesh->HasNormals()) {
			glm::vec3 normals = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex.normal = normals;
		}
		vertex.color = glm::vec3(1);

		if (mesh->mTextureCoords[0]) {
			glm::vec2 texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			vertex.texCoords = texCoord;
		}
		else
			vertex.texCoords = glm::vec2(0, 0);

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> baseColorMaps = loadMaterialTextures(material, aiTextureType_BASE_COLOR, "baseColor");
		textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<Texture> aoMaps = loadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, "ao");
		textures.insert(textures.end(), aoMaps.begin(), aoMaps.end());
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<Texture> RoughnessMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "roughness");
		textures.insert(textures.end(), RoughnessMaps.begin(), RoughnessMaps.end());
	}
	Mesh* newMesh = new Mesh(renderer, _shader, vertices, indices, textures, mesh->mName.C_Str());
	newMesh->aabbPositions = positions;
	newMesh->SetBoundingBoxPoints();
	return newMesh;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++) {
			if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture;
			texture.id = texImporter->textureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
		}
	}

	return textures;
}