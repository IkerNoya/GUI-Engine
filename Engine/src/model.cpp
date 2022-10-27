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

#define FLIPPED_IMPORT_FLAGS1 (aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals)
#define IMPORT_FLAGS1 (aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals)


Model::Model(Renderer * renderer, Shader & shader, const char* path, bool shouldFlipUVs, const char* name) : Entity(renderer) {
	texImporter = new TextureImporter;
	_renderer = renderer;
	_shader = shader;
	_name = name;
	directory = "";

	_dataManager = DataManager::Get();
	_dataManager->addEntity(this, _id);
	
	//ModelImporter::LoadModel(path, shouldFlipUVs, _root, meshes, this);
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

void Model::LoadModel(std::string path, bool shouldFlipUVs)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, shouldFlipUVs ? FLIPPED_IMPORT_FLAGS1 : IMPORT_FLAGS1);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Error::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = std::filesystem::path(path).parent_path().string();
	Mesh* baseMeshParent = new Mesh();
	baseMeshParent->SetName(scene->mRootNode->mName.C_Str());
	baseMeshParent->setParent(this);
	addChild(baseMeshParent);
	meshes.push_back(baseMeshParent);
	baseMeshParent->setNode(scene->mRootNode);

	if (baseMeshParent->getNode()->mNumChildren > 0) {
		baseMeshParent->setIsParent(true);
		parentMeshes.push_back(baseMeshParent);
	}
	if(scene)
		processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh* newMesh = processMesh(mesh, scene);
		newMesh->SetName(mesh->mName.C_Str());
		newMesh->setNode(node);
		float minX = 0;
		float maxX = 0;
		float minY = 0;
		float maxY = 0;
		float minZ = 0;
		float maxZ = 0;

		for (int k = 0; k < scene->mMeshes[node->mMeshes[i]]->mVertices->Length(); k++) {
			if (scene->mMeshes[node->mMeshes[i]]->mVertices[k].x > maxX)
				maxX = scene->mMeshes[node->mMeshes[i]]->mVertices[k].x;

			if (scene->mMeshes[node->mMeshes[i]]->mVertices[k].x < minX)
				minX = scene->mMeshes[node->mMeshes[i]]->mVertices[k].x;

			if (scene->mMeshes[node->mMeshes[i]]->mVertices[k].y > maxY)
				maxY = scene->mMeshes[node->mMeshes[i]]->mVertices[k].y;

			else if (scene->mMeshes[node->mMeshes[i]]->mVertices[k].y < minY)
				minY = scene->mMeshes[node->mMeshes[i]]->mVertices[k].y;

			if (scene->mMeshes[node->mMeshes[i]]->mVertices[k].z > maxZ)
				maxZ = scene->mMeshes[node->mMeshes[i]]->mVertices[k].z;

			if (scene->mMeshes[node->mMeshes[i]]->mVertices[k].z < minZ)
				minZ = scene->mMeshes[node->mMeshes[i]]->mVertices[k].z;
		}

		newMesh->SetMinColl(glm::vec3(minX, minY, minZ));
		newMesh->SetMaxColl(glm::vec3(maxX, maxY, maxZ));

		meshes.push_back(newMesh);
		for (int j = 0; j < parentMeshes.size(); j++) {
			if (meshes.back()->getNode()->mParent == parentMeshes[j]->getNode()) {
				meshes.back()->setParent(parentMeshes[j]);
				parentMeshes[j]->addChild(meshes.back());
				break;
			}
		}
		if (meshes.back()->getNode()->mNumChildren > 0) {
			if (!meshes.back()->IsParent()) {
				meshes.back()->setIsParent(true);
				parentMeshes.push_back(meshes.back());
			}
		}
		_dataManager->addEntity(newMesh, newMesh->GetID());
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
	if (node->mNumChildren <= 0 && meshes.back()->getParent())
		meshes.back()->SetGeneralColls((Mesh*)(meshes.back()->getParent()));
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
	//newMesh->SetBoundingBoxPoints();
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