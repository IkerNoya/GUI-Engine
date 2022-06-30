#ifndef DEBUG_H
#define DEBUG_H
#include "export.h"
#include "entity.h"

class ENGINE_API Debug : public Entity {

public:
	static void DrawLine(float x, float y);
	static void DrawSphere(float radius, float center);
	static void DrawCube(float center, float width, float height, float lenght);
};



#endif // !DEBUG_H

