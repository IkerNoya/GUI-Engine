#ifndef FRUSTRUM_H
#define FRUSTRUM_H
#include "../export.h"
#include "plane.h"

struct ENGINE_API Frustrum{
	Plane Top;
	Plane Bottom;
	Plane Left;
	Plane Right;
	Plane Near;
	Plane Far;
};

Frustrum GetFrustrumFromCamera(class Camera* camera, float aspect, float fov, float near, float far); 

#endif // !FRUSTRUM_H

