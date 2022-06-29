#ifndef SCENE_NODE_H
#define SCENE_NODE_H
#define SCENE_NODE_H
#include "export.h"
#include "entity.h"
#include <vector>

class Mesh;
class Renderer;
class Shader;
class TextureImporter;
struct Texture;

struct aiNode;
struct aiScene;
struct aiMesh;
enum aiTextureType;
struct aiMaterial;

class ENGINE_API SceneNode : public Entity{
	std::vector<Mesh*> meshes;
	std::vector<SceneNode*> nodes;
	aiNode* _rootNode;
	std::string _directory;

	TextureImporter* texImporter;
	Renderer* _renderer;
	Shader _shader;

	Mesh* processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Texture>& loadedTextures);
	void processNode(aiNode* node, const aiScene* scene, std::vector<Texture>& loadedTextures);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::vector<Texture>& loadedTextures);

public:
	SceneNode(Renderer* renderer, Shader& shader, std::string directory, aiNode* node, const aiScene* scene, std::vector<Texture>& loadedTextures);
	~SceneNode();
	
	void draw();

	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;

	virtual void setColor(float r, float g, float b) override;

};

#endif // !SCENE_NODE_H

