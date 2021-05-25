#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "shader.h"

#include <fstream>
#include <sstream> // to read and write strings in files

Shader::Shader() {
	_id = 0;
}

Shader::~Shader() {

}

void Shader::createShader(const char* vertexPath, const char* fragmentPath) {
	// ------------------Find Shader-----------------
	std::string vertex;
	std::string fragment;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	std::stringstream vertexBuffer;
	std::stringstream fragmentBuffer;

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

	vertex = vertexBuffer.str();
	fragment = fragmentBuffer.str();

	// -----------Compile------------------

	_id = glCreateProgram();
	unsigned int vertexID = compileShader(GL_VERTEX_SHADER, vertex);
	unsigned int fragmentID = compileShader(GL_FRAGMENT_SHADER, fragment);
	glAttachShader(_id, vertexID);
	glAttachShader(_id, fragmentID);

	glLinkProgram(_id);
	glValidateProgram(_id);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
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