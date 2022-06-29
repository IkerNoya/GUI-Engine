#include "sceneNode.h"
#include "renderer.h"
#include "shader.h"
#include "mesh.h"
#include "texture_importer.h"
#include "dataManager.h"

#include <string>
#include <filesystem>

#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"


SceneNode::SceneNode(Renderer* renderer, Shader& shader, std::string directory, aiNode* node, const aiScene* scene, std::vector<Texture>& loadedTextures) : Entity(renderer) {
	texImporter = new TextureImporter();
	_renderer = renderer;
	_shader = shader;
	_directory = directory;
	_rootNode = node;

	_name = node->mName.C_Str();
	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);


	processNode(node, scene, loadedTextures);
}

SceneNode::~SceneNode(){
	if (!meshes.empty()) {
		for (auto* mesh : meshes) {
			if (mesh) {
				delete mesh;
				mesh = nullptr;
			}
		}
		meshes.clear();
	}

	if (!nodes.empty()) {
		for (auto* child : nodes) {
			if (child) {
				delete child;
				child = nullptr;
			}
		}
		nodes.clear();
	}

	if (texImporter) {
		delete texImporter;
		texImporter = nullptr;
	}
}

void SceneNode::draw()
{
	updateSelfAndChild();
	updateVectors();
	if (!ShouldDraw())
		return;

	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i]->Draw(getModelMatrix());
	for (auto* node : nodes)
		if (node)
			node->draw();
}

void SceneNode::setColor(glm::vec3 color)
{
}

void SceneNode::setColor(float r, float g, float b)
{
}



Mesh* SceneNode::processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Texture>& loadedTextures){
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		glm::vec3 vec = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.position = vec;
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
		std::vector<Texture> baseColorMaps = loadMaterialTextures(material, aiTextureType_BASE_COLOR, "baseColor", loadedTextures);
		textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse", loadedTextures);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular", loadedTextures);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<Texture> aoMaps = loadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, "ao", loadedTextures);
		textures.insert(textures.end(), aoMaps.begin(), aoMaps.end());
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "normal", loadedTextures);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<Texture> RoughnessMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "roughness", loadedTextures);
		textures.insert(textures.end(), RoughnessMaps.begin(), RoughnessMaps.end());
	}
	return new Mesh(_renderer, _shader, vertices, indices, textures, mesh->mName.C_Str());
}

void SceneNode::processNode(aiNode* node, const aiScene* scene, std::vector<Texture>& loadedTextures)
{
	_rootNode = node;
	//if (node != scene->mRootNode) {
		for (unsigned short i = 0; i < node->mNumMeshes; i++) {
			if (node->mMeshes[i]) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				Mesh* newMesh = processMesh(mesh, scene, loadedTextures);
				addChild(newMesh);
				meshes.push_back(newMesh);
			}
		}
		std::cout  << node->mName.C_Str() << " has " << meshes.size() << " meshes" << std::endl;
	//}
	for (unsigned short i = 0; i < node->mNumChildren; i++) {
		if (node->mChildren[i]) {
			auto* sceneNode = new SceneNode(_renderer, _shader, _directory, node->mChildren[i], scene, loadedTextures);
			addChild(sceneNode);
			nodes.push_back(sceneNode);
		}
		std::cout  << nodes.back()->_name << " has " << nodes.back()->nodes.size() << " nodes" << std::endl;
	}
		std::cout  << _name << " has " << children.size() << " chidren" << std::endl;
}

std::vector<Texture> SceneNode::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::vector<Texture>& loadedTextures)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < loadedTextures.size(); j++) {
			if (std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture;
			texture.id = texImporter->textureFromFile(str.C_Str(), _directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}

	return textures;
}
