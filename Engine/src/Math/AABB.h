#ifndef AABB_H
#define AABB_H
#include "../export.h"
#include"../entity.h"

class ENGINE_API AABB : public Entity{
	bool isOnFrustrum = true;

public:
	AABB();
	~AABB();

	void attachToEntity(ModelMatrix model, Transform transformAttached);
	void updateModel(ModelMatrix model, Transform transformAttached);
	void draw(class Line* line);
};


#endif // !AABB_H

