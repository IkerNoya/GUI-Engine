#ifndef MATERIALS_H
#define MATERIALS_H
#include "export.h"
#include "glm.hpp"
struct Material {
	float shininess;

	unsigned int diffuseTexture;
	unsigned int specularTexture;
};


#endif // !MATERIALS_H

