#ifndef CAMERA_H
#define CAMERA_H
#include "export.h"
#include "entity.h"
#include "glm.hpp"

enum class ENGINE_API ProjectionType{
	orthographic, perspective
};

enum class ENGINE_API CameraType {
	fps, tps
};
class ENGINE_API Camera : public Entity {
	ProjectionType _type;

	glm::mat4 _view;
	glm::mat4 _proj;
	glm::vec3 _right;
	glm::vec3 _up;
	glm::vec3 _worldUp;
	glm::vec3 _forward;
	glm::vec3 _inverseDirection;

	class Window* _window;

	float pitch;
	float yaw;

public: 
	float rotationSpeed = 10;
	float movementSpeed = 0;

	Camera(class Window* window, Renderer* renderer,ProjectionType type);
	~Camera();
	void updateView();
	void setProjection(ProjectionType type);
	void init(Shader& shader);
	glm::mat4 getView();
	glm::mat4 getProjection();
	ProjectionType getProjectionType();
	void draw(Shader& shader);
	void setDirection(glm::vec3 target);
	glm::vec3 getForward();
	glm::vec3 getUp();
	glm::vec3 getRight();
	void rotatePitch(float pitch);
	void rotateYaw(float yaw);
private:
	void updateShader(Shader& shader);
	void updateVectors();

	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;
	virtual void setColor(float r, float g, float b) override;
};

#endif // !CAMERA_H

