#ifndef SHADER_H
#define SHADER_H
#include "export.h"
#include <iostream>
#include <glm.hpp>

class ENGINE_API Shader {
	unsigned int _id;
public:
	Shader();
	~Shader();
	void createShader(const char* vertexPath, const char* fragmentPath);
	unsigned int getID();
	void useProgram();
	unsigned int compileShader(unsigned int type, std::string& source);
	void setVec3(const char* name, float x, float y, float z);
	void setVec3(const char* name, glm::vec3 value);
	void setMat4(const char* name, glm::mat4 value);
	void setAttribute(const char* name, int dataAmount, int dataSize, int dataPosition);
	void setSampler2D(const char* name);
};

#endif // !SHADER_H

