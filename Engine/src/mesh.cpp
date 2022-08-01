#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "mesh.h"
#include "shader.h"
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

Mesh::Mesh(Renderer* renderer, Shader& shader, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, const char* name) : Entity(renderer)
{
	this->shader = shader;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	_renderer = renderer;
	boundingBox = new AABB();

	std::string sufix = " - mesh";
	std::string newName = name + sufix;
	_name = newName;

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
	boundingBox->attachToEntity(modelMatrix, transform);
	boundingBox->setVerticesColliders(boundingBox->generateAABB_pos(aabbPositions));

	setupMesh();
}

Mesh::~Mesh()
{
	if (boundingBox) delete boundingBox;
}

void Mesh::Draw(Line* line)
{
	updateSelfAndChild();
	updateVectors();
	if (boundingBox)
		boundingBox->draw(line);
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

void Mesh::setColor(glm::vec3 color)
{
}

void Mesh::setColor(float r, float g, float b)
{
}
