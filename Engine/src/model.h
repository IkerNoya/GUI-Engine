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
	std::vector<Mesh*> parentMeshes;
	Entity* _root;
	//std::vector<Entity*> _rootChildren;
	std::string directory;
	Shader _shader;
	Renderer* renderer;
	DataManager* _dataManager;

public:
	std::vector<Texture> texturesLoaded;
	Mesh* baseMeshParent;

	Model(Renderer* renderer, Shader& shader, const char *name);
	~Model();
	void draw(Line* line);


	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;

	virtual void setColor(float r, float g, float b) override;

	void AddMesh(Mesh* mesh);
	void AddParentMesh(Mesh* mesh);

	inline std::vector<Mesh*> GetMeshes() { return meshes; }
	inline std::vector<Mesh*> GetParentMeshes() { return parentMeshes; }

};

#endif // !MODEL_H
