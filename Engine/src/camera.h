#ifndef CAMERA_H
#define CAMERA_H
#include "export.h"
#include "entity.h"
#include "glm.hpp"

enum class ENGINE_API ProjectionType{
	orthographic, perspective
};
class ENGINE_API Camera : public Entity {
	ProjectionType _type;
	glm::mat4 _view;
	glm::mat4 _proj;

public:
	Camera(Renderer* renderer,ProjectionType type);
	~Camera();
	void setView(glm::vec3 direction, glm::vec3 up);
	void setProjection(ProjectionType type);
	glm::mat4 getView();
	glm::mat4 getProjection();
	void draw(Shader& shader);
};

#endif // !CAMERA_H

