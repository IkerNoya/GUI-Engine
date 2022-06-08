#ifndef MODEL_H
#define MODEL_H

#include "entity.h"
#include "export.h"
#include "mesh.h"
#include <vector>
#include <string>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
class Shader;
class Renderer;
class TextureImporter;

class ENGINE_API ModelMat : public Entity {
	std::vector<Mesh> meshes;
	std::string directory;
	Shader _shader;
	Renderer* renderer;
	TextureImporter* texImporter;

	void LoadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	ModelMat(Renderer* renderer, Shader& shader, char* path);

};

#endif // !MODEL_H
