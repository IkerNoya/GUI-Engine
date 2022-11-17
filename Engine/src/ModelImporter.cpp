#include "ModelImporter.h"
#include "dataManager.h"
#include "texture_importer.h"

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

void ModelImporter::Load(Model* model, std::string path, bool shouldFlipUVs)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, shouldFlipUVs ? FLIPPED_IMPORT_FLAGS1 : IMPORT_FLAGS1);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Error::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = std::filesystem::path(path).parent_path().string();
	model->baseMeshParent = new Mesh();

	model->baseMeshParent->SetName(scene->mRootNode->mName.C_Str());
	model->baseMeshParent->setParent(model);

	model->addChild(model->baseMeshParent);
	model->AddMesh(model->baseMeshParent);
	model->baseMeshParent->setNode(scene->mRootNode);

	if (model->baseMeshParent->getNode()->mNumChildren > 0) {
		model->baseMeshParent->setIsParent(true);
		model->AddParentMesh(model->baseMeshParent);
	}

	if (scene)
		processNode(model, scene->mRootNode, scene);
}

void ModelImporter::LoadFromNode(Model* model, aiNode* node, bool shouldFlipUVs, const aiScene* scene)
{

	model->baseMeshParent = new Mesh();

	model->baseMeshParent->SetName(node->mName.C_Str());
	model->baseMeshParent->setParent(model);

	model->addChild(model->baseMeshParent);
	model->AddMesh(model->baseMeshParent);
	model->baseMeshParent->setNode(node);

	model->baseMeshParent->setIsParent(true);
	model->AddParentMesh(model->baseMeshParent);

	if (node)
		processNode(model, node, scene);
}

void ModelImporter::processNode(Model* model, aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh* newMesh = processMesh(model, mesh, scene);
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

		model->AddMesh(newMesh);
		for (int j = 0; j < model->GetParentMeshes().size(); j++) {
			if (model->GetMeshes().back()->getNode()->mParent == model->GetParentMeshes()[j]->getNode()) {
				model->GetMeshes().back()->setParent(model->GetParentMeshes()[j]);
				model->GetParentMeshes()[j]->addChild(model->GetMeshes().back());
				break;
			}
		}
		if (model->GetMeshes().back()->getNode()->mNumChildren > 0) {
			if (!model->GetMeshes().back()->IsParent()) {
				model->GetMeshes().back()->setIsParent(true);
				model->AddParentMesh(model->GetMeshes().back());
			}
		}
		_dataManager->addEntity(newMesh, newMesh->GetID());
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(model, node->mChildren[i], scene);
	}
	if (node->mNumChildren <= 0 && model->GetMeshes().back()->getParent())
		model->GetMeshes().back()->SetGeneralColls((Mesh*)(model->GetMeshes().back()->getParent()));
}

Mesh* ModelImporter::processMesh(Model* model, aiMesh* mesh, const aiScene* scene)
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
		std::vector<Texture> baseColorMaps = loadMaterialTextures(model, material, aiTextureType_BASE_COLOR, "baseColor");
		textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
		std::vector<Texture> diffuseMaps = loadMaterialTextures(model, material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(model, material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<Texture> aoMaps = loadMaterialTextures(model, material, aiTextureType_AMBIENT_OCCLUSION, "ao");
		textures.insert(textures.end(), aoMaps.begin(), aoMaps.end());
		std::vector<Texture> normalMaps = loadMaterialTextures(model, material, aiTextureType_NORMALS, "normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<Texture> RoughnessMaps = loadMaterialTextures(model, material, aiTextureType_DIFFUSE_ROUGHNESS, "roughness");
		textures.insert(textures.end(), RoughnessMaps.begin(), RoughnessMaps.end());
	}
	Mesh* newMesh = new Mesh(renderer, _shader, vertices, indices, textures, mesh->mName.C_Str());
	newMesh->aabbPositions = positions;
	//newMesh->SetBoundingBoxPoints();
	return newMesh;
}

std::vector<Texture> ModelImporter::loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < model->texturesLoaded.size(); j++) {
			if (std::strcmp(model->texturesLoaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(model->texturesLoaded[j]);
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
			model->texturesLoaded.push_back(texture);
		}
	}
}

ModelImporter::ModelImporter()
{
	texImporter = new TextureImporter();
	_dataManager = DataManager::Get();
}

Model* ModelImporter::LoadModel(const char* path, bool shouldFlipUVs, const char* name)
{
    Model* model = new Model(renderer, _shader, name);
	Load(model, path, shouldFlipUVs);

    return model;
}

std::vector<Model*> ModelImporter::LoadScene(const char* path, bool shouldFlipUVs)
{
    std::vector<Model*> models;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, shouldFlipUVs ? FLIPPED_IMPORT_FLAGS1 : IMPORT_FLAGS1);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Error::ASSIMP::" << importer.GetErrorString() << std::endl;
		return models;
	}
	directory = std::filesystem::path(path).parent_path().string();
	for (int i = 0; i < scene->mRootNode->mNumChildren; i++) {
		Model* model = new Model(renderer, _shader, scene->mRootNode->mChildren[i]->mName.C_Str());
		LoadFromNode(model, scene->mRootNode->mChildren[i], shouldFlipUVs, scene);
		models.push_back(model);
		std::cout << "HIjo: " << scene->mRootNode->mChildren[i]->mName.C_Str() << std::endl;
	}

    return models;
}
