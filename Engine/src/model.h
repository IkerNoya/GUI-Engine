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
class SceneNode;

struct  aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

class ENGINE_API Model : public Entity {
	std::vector<Mesh*> meshes;
	std::vector<Texture> texturesLoaded;
	SceneNode* _root;
	std::vector<SceneNode*> _rootChildren;
	std::string directory;
	Shader _shader;
	Renderer* renderer;
	TextureImporter* texImporter;


	void LoadModel(std::string path, bool shouldFlipUVs);
	void processNode(aiNode* node, const aiScene* scene, Entity* parent);

public:
	Model(Renderer* renderer, Shader& shader,const char* path, bool shouldFlipUVs, const char* name);
	~Model();
	void draw();


	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;

	virtual void setColor(float r, float g, float b) override;

};

#endif // !MODEL_H
