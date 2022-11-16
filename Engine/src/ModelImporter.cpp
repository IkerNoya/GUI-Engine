#include "ModelImporter.h"

ModelImporter::ModelImporter()
{
}

Model* ModelImporter::LoadModel(Renderer* renderer, Shader& shader, const char* path, bool shouldFlipUVs, const char* name)
{
    return nullptr;
}

std::vector<Model*> ModelImporter::LoadScene(Renderer* renderer, Shader& shader, const char* path, bool shouldFlipUVs)
{
    return std::vector<Model*>();
}
