#ifndef ENTITY_H
#define ENTITY_H
#include "export.h"
#include "renderer.h"
#include "mat4x4.hpp"
#include <vector>
#include "gtc/quaternion.hpp"

// using glm vec3 temporarily, will later use my
struct ENGINE_API Rotation {
	glm::mat4 x;
	glm::mat4 y;
	glm::mat4 z;
};

struct ENGINE_API ModelMatrix {
	glm::mat4 translate;
	glm::mat4 rotMatrix;
	Rotation rotation;
	glm::mat4 scale;
	glm::mat4 trs;
};

struct ENGINE_API Transform {
	glm::vec3 position;
	glm::quat rotationQuat;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
};

//basic enitity for now
class ENGINE_API Entity {
protected:
	int _id;
	static int _nextEntityID;
	std::string _name = "";
	Renderer* _renderer;
	ModelMatrix modelMatrix;
	bool _isLightSource = false;
	bool _shouldDraw = true;
	bool _isParent = false;
	Shader _entityShader;

	std::vector<Entity*> children;
	Entity* parent;

	void updateModel();
	void updateUp();
	void updateRight();
	void updateForward();
public:
	void updateMatrices();
	Entity();
	Entity(Renderer* renderer);
	~Entity();
	Transform transform;
	Renderer* GetRenderer();
	glm::mat4 getModelMatrix();
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetID(int id);
	int GetID();
	void SetName(std::string name);
	void setEntityColor(glm::vec3 color);
	virtual void setColor(glm::vec3 color);
	virtual void setColor(float r, float g, float b);
	void addChild(Entity* entity);
	void setRenderer(Renderer* renderer);
	virtual void setShader(Shader& shader);
	void SetRot(float x, float y, float z);
	void SetRot(glm::vec3 euler);
	void SetRot(glm::quat quaternion);

protected:
	void ComputeModelMatrix();
	void ComputeModelMatrix(const glm::mat4& parentModelMatrix);
	void updateSelfAndChild();
	void updateVectors();

public:
	void setParent(Entity* newParent);
	void setIsParent(bool isParent);
	std::string GetName();
	inline virtual glm::vec3 getColor() const { return glm::vec3(1); };
	inline bool IsLightSource() { return _isLightSource; }
	inline Shader GetShader() { return _entityShader; }
	inline virtual bool ShouldDraw() const { return _shouldDraw; }
	virtual void show(bool value);
	inline std::vector<Entity*> getChildren() { return children; }
	inline Entity* getParent() { return parent; }
	inline bool IsParent() const { return _isParent; }
	inline glm::vec3 getGlobalPosition() const { return modelMatrix.trs[3]; }
	glm::quat EulerToQuat(glm::vec3 euler);
	glm::vec3 QuatXVec(glm::quat quat, glm::vec3 vec);
	inline glm::vec3 getGlobalScale() const { return glm::vec3(glm::length(modelMatrix.trs[0]), glm::length(modelMatrix.trs[1]), glm::length(modelMatrix.trs[2])); }
	inline glm::vec3 getForward() const { return transform.forward; }
	inline glm::vec3 getRight() const { return transform.right; }
	inline glm::vec3 getBack() const { return -transform.forward; }
	inline glm::vec3 getUp() const { return transform.up; }

private:
	glm::mat4 getLocalModelMatrix();
};

#endif // !ENTITY_H
