#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "mesh.h"
#include "shader.h"
#include <string>

void Mesh::setupMesh()
{

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	_renderer->setMeshAttribPointers(shader, sizeof(Vertex), 0, offsetof(Vertex, color), offsetof(Vertex, normal), offsetof(Vertex, texCoords));

}

Mesh::Mesh(Renderer* renderer, Shader& shader, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : Entity(renderer)
{
	this->shader = shader;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	_renderer = renderer;

	setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::Draw()
{
	updateMatrices();
	updateVectors();

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
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	_renderer->setMeshAttribPointers(shader, sizeof(Vertex), 0, offsetof(Vertex, color), offsetof(Vertex, normal), offsetof(Vertex, texCoords));
	shader.useProgram();
	shader.setMat4("transform", GetModelMatrix());
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void Mesh::setColor(glm::vec3 color)
{
}

void Mesh::setColor(float r, float g, float b)
{
}
