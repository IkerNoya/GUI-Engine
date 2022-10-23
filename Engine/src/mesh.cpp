#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "mesh.h"
#include "shader.h"
#include "assimp/scene.h"
#include <string>

#include "dataManager.h"

void Mesh::setupMesh()
{
	_renderer->generateVAO(vao);

	_renderer->bindVAO(vao);

	_renderer->generateVBO(vbo);

	_renderer->bindMeshVBO(vbo, vertices.size() * sizeof(Vertex), &vertices[0]);

	_renderer->bindMeshEBO(ebo, &indices[0], indices.size() * sizeof(unsigned int));

	_renderer->setMeshAttribPointers(shader, sizeof(Vertex), 0, offsetof(Vertex, color), offsetof(Vertex, normal), offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

Mesh::Mesh()
{
}

Mesh::Mesh(Renderer* renderer, Shader& shader, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, const char* name) : Entity(renderer)
{
	this->shader = shader;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	_renderer = renderer;

	std::string sufix = " - mesh";
	std::string newName = name + sufix;
	_name = newName;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);

	_minCollConst = glm::vec3(999, 999, 999);
	_minColl = glm::vec3(999, 999, 999);
	_maxCollConst = glm::vec3(-999, -999, -999);
	_maxColl = glm::vec3(-999, -999, -999);

	_minCollTotal = glm::vec3(999, 999, 999);
	_maxCollTotal = glm::vec3(-999, -999, -999);

	setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Line* line)
{
	updateSelfAndChild();
	updateVectors();
	UpdateColliderPos();
	UpdateColliderScale();
	if (!ShouldDraw()) return;
	line->draw(GetMinCollGeneral(), GetMaxCollGeneral(), glm::vec3(0, 1, 0));
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures[i].type;

		if (name == "diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "specular")
			number = std::to_string(specularNr++);

		shader.setInt(("material." + name /*+ number*/).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	_renderer->bindVAO(vao);
	_renderer->bindMeshVBO(vbo, vertices.size() * sizeof(Vertex), &vertices[0]);
	_renderer->setMeshAttribPointers(shader, sizeof(Vertex), 0, offsetof(Vertex, color), offsetof(Vertex, normal), offsetof(Vertex, texCoords));
	shader.useProgram();
	shader.setMat4("transform", getModelMatrix());
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	_renderer->unbindBuffers();
}

void Mesh::SetMinColl(glm::vec3 value)
{
	_minCollConst = value;
	_minColl = (_minCollConst * getGlobalScale()) + getGlobalPosition();
}

void Mesh::SetMaxColl(glm::vec3 value)
{
	_maxCollConst = value;
	_maxColl = (_maxCollConst * getGlobalScale()) + getGlobalPosition() + (-_minCollConst * getGlobalScale());
}

glm::vec3 Mesh::GetMinCollTotal()
{
	return _minCollConst;
}

glm::vec3 Mesh::GetMaxCollTotal()
{
	return _maxCollConst;
}

glm::vec3 Mesh::GetMinColl()
{
	return _minColl;
}

glm::vec3 Mesh::GetMaxColl()
{
	return _maxColl;
}

void Mesh::SetMinCollGeneral(glm::vec3 value)
{
	_minCollTotal = value;
}

void Mesh::SetMaxCollGeneral(glm::vec3 value)
{
	_maxCollTotal = value;
}

glm::vec3 Mesh::GetMinCollGeneral()
{
	return _minCollTotal;
}

glm::vec3 Mesh::GetMaxCollGeneral()
{
	return _maxCollTotal;
}

void Mesh::SetGeneralColls(Mesh* mesh)
{
	float minX = mesh->GetMinColl().x, minY = mesh->GetMinColl().y, minZ = mesh->GetMinColl().z, maxX = mesh->GetMaxColl().x, maxY = mesh->GetMaxColl().y, maxZ = mesh->GetMaxColl().z;
	mesh->SetMinCollGeneral(glm::vec3(minX, minY, minZ));
	mesh->SetMaxCollGeneral(glm::vec3(maxX, maxY, maxZ));

	for (int i = 0; i < mesh->getChildren().size(); i++)
		SetGeneralColls((Mesh*)mesh->getChildren()[i]);

	if (mesh->getParent() != NULL) {
		if (!mesh->IsParent())
			mesh->TryChangeParentGeneralColls((Mesh*)mesh->getParent());
		else
			mesh->TryChangeParentGeneralCollsWhenYouAreParent((Mesh*)mesh->getParent());
	}
}

void Mesh::TryChangeParentGeneralColls(Mesh* mesh)
{
	float minX = mesh->GetMinColl().x, minY = mesh->GetMinColl().y, minZ = mesh->GetMinColl().z, maxX = mesh->GetMaxColl().x, maxY = mesh->GetMaxColl().y, maxZ = mesh->GetMaxColl().z;

	for (int i = 0; i < mesh->getChildren().size(); i++) {

		if (((Mesh*)mesh->getChildren()[i])->GetMinColl().x <= minX)
			minX = ((Mesh*)mesh->getChildren()[i])->GetMinColl().x;

		if (((Mesh*)mesh->getChildren()[i])->GetMinColl().y <= minY)
			minY = ((Mesh*)mesh->getChildren()[i])->GetMinColl().y;

		if (((Mesh*)mesh->getChildren()[i])->GetMinColl().z <= minZ)
			minZ = ((Mesh*)mesh->getChildren()[i])->GetMinColl().z;

		if (((Mesh*)mesh->getChildren()[i])->GetMaxColl().x >= maxX)
			maxX = ((Mesh*)mesh->getChildren()[i])->GetMaxColl().x;

		if (((Mesh*)mesh->getChildren()[i])->GetMaxColl().y >= maxY)
			maxY = ((Mesh*)mesh->getChildren()[i])->GetMaxColl().y;

		if (((Mesh*)mesh->getChildren()[i])->GetMaxColl().z >= maxZ)
			maxZ = ((Mesh*)mesh->getChildren()[i])->GetMaxColl().z;
	}

	mesh->SetMinCollGeneral(glm::vec3(minX, minY, minZ));
	mesh->SetMaxCollGeneral(glm::vec3(maxX, maxY, maxZ));
}

void Mesh::TryChangeParentGeneralCollsWhenYouAreParent(Mesh* mesh)
{
	float minX = mesh->GetMinCollGeneral().x, minY = mesh->GetMinCollGeneral().y, minZ = mesh->GetMinCollGeneral().z, maxX = mesh->GetMaxCollGeneral().x, maxY = mesh->GetMaxCollGeneral().y, maxZ = mesh->GetMaxCollGeneral().z;

	for (int i = 0; i < mesh->getChildren().size(); i++) {
		if (((Mesh*)mesh->getChildren()[i])->GetMinCollGeneral().x <= minX)
			minX = ((Mesh*)mesh->getChildren()[i])->GetMinCollGeneral().x;

		if (((Mesh*)mesh->getChildren()[i])->GetMinCollGeneral().y <= minY)
			minY = ((Mesh*)mesh->getChildren()[i])->GetMinCollGeneral().y;

		if (((Mesh*)mesh->getChildren()[i])->GetMinCollGeneral().z <= minZ)
			minZ = ((Mesh*)mesh->getChildren()[i])->GetMinCollGeneral().z;

		if (((Mesh*)mesh->getChildren()[i])->GetMaxCollGeneral().x >= maxX)
			maxX = ((Mesh*)mesh->getChildren()[i])->GetMaxCollGeneral().x;

		if (((Mesh*)mesh->getChildren()[i])->GetMaxCollGeneral().y >= maxY)
			maxY = ((Mesh*)mesh->getChildren()[i])->GetMaxCollGeneral().y;

		if (((Mesh*)mesh->getChildren()[i])->GetMaxCollGeneral().z >= maxZ)
			maxZ = ((Mesh*)mesh->getChildren()[i])->GetMaxCollGeneral().z;
	}

	mesh->SetMinCollGeneral(glm::vec3(minX, minY, minZ));
	mesh->SetMaxCollGeneral(glm::vec3(maxX, maxY, maxZ));
}

void Mesh::UpdateColliderScale()
{
	_minColl = (_minCollConst * getGlobalScale()) + getGlobalPosition();
	_maxColl = (_maxCollConst * getGlobalScale()) + getGlobalPosition() + (-_minCollConst * getGlobalScale());

	if (!IsParent()) {
		_minCollTotal = _minColl;
		_maxCollTotal = _maxColl;
	}

	for (int i = 0; i < getChildren().size(); i++)
		((Mesh*)getChildren()[i])->UpdateColliderScale();
}

void Mesh::UpdateColliderPos()
{
	_minColl = (_minCollConst * getGlobalScale()) + getGlobalPosition();
	_maxColl = (_maxCollConst * getGlobalScale()) + getGlobalPosition() + (-_minCollConst * getGlobalScale());

	if (!IsParent()) {
		_minCollTotal = _minColl;
		_maxCollTotal = _maxColl;
	}

	for (int i = 0; i < getChildren().size(); i++)
		((Mesh*)getChildren()[i])->UpdateColliderPos();

}

void Mesh::setColor(glm::vec3 color)
{
}

void Mesh::setColor(float r, float g, float b)
{
}

void Mesh::setNode(aiNode* newNode)
{
	node = newNode;
}
