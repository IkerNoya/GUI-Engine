#ifndef MODEL_H
#define MODEL_H

#include "entity.h"
#include "export.h"
#include "mesh.h"
#include <vector>
#include <string>

class Shader;
class Renderer;
class TextureImporter;
class DataManager;

struct  aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

class ENGINE_API Model : public Entity {
	std::vector<Mesh*> meshes;
	std::vector<Texture> texturesLoaded;
	Entity* _root;
	std::vector<Entity*> _rootChildren;
	std::string directory;
	Shader _shader;
	Renderer* renderer;
	TextureImporter* texImporter;
	DataManager* _dataManager;


	void LoadModel(std::string path, bool shouldFlipUVs);
	void processNode(aiNode* node, const aiScene* scene, Entity* parent);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	Model(Renderer* renderer, Shader& shader,const char* path, bool shouldFlipUVs, const char* name);
	~Model();
	void draw(Line* line);


	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;

	virtual void setColor(float r, float g, float b) override;

};

#endif // !MODEL_H
