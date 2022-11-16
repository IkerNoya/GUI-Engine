#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H
#include "export.h"
#include "model.h"
#include <vector>

class ENGINE_API ModelImporter {
public:
	ModelImporter();
	Model* LoadModel(Renderer* renderer, Shader& shader, const char* path, bool shouldFlipUVs, const char* name);
	std::vector<Model*> LoadScene(Renderer* renderer, Shader& shader, const char* path, bool shouldFlipUVs);
};

#endif // !MODEL_IMPORTER_H


