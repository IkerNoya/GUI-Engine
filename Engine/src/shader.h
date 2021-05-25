#ifndef SHADER_H
#define SHADER_H
#include "export.h"
#include <iostream>

class ENGINE_API Shader {
	unsigned int _id;
public:
	Shader();
	~Shader();
	void createShader(const char* vertexPath, const char* fragmentPath);
	unsigned int getID();
	void useProgram();
	unsigned int compileShader(unsigned int type, std::string& source);
};

#endif // !SHADER_H

