#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H
#include "export.h"
#include "model.h"
#include <vector>

class ENGINE_API ModelImporter {
private:
	//std::vector<Entity*> _rootChildren;
	std::string directory;
	Shader _shader;
	Renderer* renderer;
	TextureImporter* texImporter;
	DataManager* _dataManager;

	void Load(Model* model, std::string path, bool shouldFlipUVs);
	void LoadFromNode(Model* model, aiNode* node, bool shouldFlipUVs, const aiScene* scene);
	void processNode(Model* model, aiNode* node, const aiScene* scene);
	Mesh* processMesh(Model* model, aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	ModelImporter();
	Model* LoadModel(const char* path, bool shouldFlipUVs, const char* name);
	std::vector<Model*> LoadScene(const char* path, bool shouldFlipUVs);

	void SetRenderer(Renderer* renderer) { this->renderer = renderer; }
	void SetShader(Shader& shader) { _shader = shader; }
	
};

#endif // !MODEL_IMPORTER_H


