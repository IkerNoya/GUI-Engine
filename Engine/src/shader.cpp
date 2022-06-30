#include "GL/glew.h"

#include "shader.h"

#include <fstream>
#include <sstream> // to read and write strings in files
#include <glm.hpp>
#include	"gtc/type_ptr.hpp"

Shader::Shader() {
	_id = 0;
}

Shader::~Shader() {

}

void Shader::createShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	// ------------------Find Shader-----------------
	std::string vertex;
	std::string fragment;
	std::string geometry;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::ifstream geometryFile;

	std::stringstream vertexBuffer;
	std::stringstream fragmentBuffer;
	std::stringstream geometryBuffer;

	vertexFile.open(vertexPath);
	if (vertexFile.is_open()) {
		vertexBuffer << vertexFile.rdbuf();
		vertexFile.close();
	}
	else {
		std::cout << "Couldn't open vertex file" << std::endl;
	}

	fragmentFile.open(fragmentPath);
	if (fragmentFile.is_open()) {
		fragmentBuffer << fragmentFile.rdbuf();
		fragmentFile.close();
	}
	else {
		std::cout << "Couldn't open fragment file" << std::endl;
	}

	if (geometryPath != nullptr) {
		geometryFile.open(geometryPath);
		if (geometryFile.is_open()) {
			geometryBuffer << geometryFile.rdbuf();
			geometryFile.close();
		}
		else {
			std::cout << "Couldn't open fragment file" << std::endl;
		}
		geometry = geometryBuffer.str();
	}

	vertex = vertexBuffer.str();
	fragment = fragmentBuffer.str();

	// -----------Compile------------------

	_id = glCreateProgram();
	unsigned int vertexID = compileShader(GL_VERTEX_SHADER, vertex);
	unsigned int fragmentID = compileShader(GL_FRAGMENT_SHADER, fragment);
	unsigned int geometryId = 0;
	if(geometryPath!=nullptr)
		geometryId = compileShader(GL_GEOMETRY_SHADER, geometry);
	
	glAttachShader(_id, vertexID);
	glAttachShader(_id, fragmentID);
	if (geometryPath != nullptr)
		glAttachShader(_id, geometryId);

	glLinkProgram(_id);
	glValidateProgram(_id);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	if (geometryPath != nullptr)
		glDeleteShader(geometryId);
}

unsigned int Shader::getID() {
	return _id;
}

void Shader::useProgram() {
	glUseProgram(_id);
}

unsigned int Shader::compileShader(unsigned int type, std::string& source) {
	unsigned int shaderID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shaderID);
		return 0;
	}
	return shaderID;
}

void Shader::setInt(const char* name, int value)
{
	GLint attribLocation = glGetUniformLocation(_id, name);
	glProgramUniform1i(_id, attribLocation, value);
}

void Shader::setFloat(const char* name, float value)
{
	GLint attribLocation = glGetUniformLocation(_id, name);
	// glUniform1f is deprecated
	glProgramUniform1f(_id, attribLocation, value);
}

void Shader::setVec3(const char* name, float x, float y, float z)
{
	glm::vec3 value = glm::vec3(x, y, z);
	GLint attribLocation = glGetUniformLocation(_id, name);
	glProgramUniform3fv(_id, attribLocation, 1, glm::value_ptr(value));
}

void Shader::setVec3(const char* name, glm::vec3 value)
{
	GLint attribLocation = glGetUniformLocation(_id, name);
	glProgramUniform3fv(_id, attribLocation, 1, glm::value_ptr(value));
}

void Shader::setMat4(const char* name, glm::mat4 value)
{
	GLint attribLocation = glGetUniformLocation(_id, name);
	glUniformMatrix4fv(attribLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setAttribute(const char* name, int dataAmount, int dataSize, int dataPosition)
{
	unsigned int attrib = glGetAttribLocation(_id, name);
	glVertexAttribPointer(attrib, dataAmount, GL_FLOAT, GL_FALSE, sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(attrib);
}

void Shader::setSampler2D(const char* name)
{
	glUniform1i((glGetUniformLocation(_id, name)), 0);
}

