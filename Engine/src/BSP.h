#ifndef BSP_H

#include "export.h"
#include "entity.h"
#include "model.h"
#include <vector>

struct ENGINE_API BSPlane {
	Model* model;
	glm::vec3 angleLookA;
	glm::vec3 angleLookB;
};

class ENGINE_API BSP : public Entity
{
	std::vector<BSPlane> _planes;
	std::vector<Model*> _models;
	Shader _shader;
public:
	BSP(Shader& shader);
	~BSP();

	void check();
	void checkObject(Mesh* mesh);
	void checkPlaneCamera(Entity* camera);
	void addPlane(Model* model, glm::vec3 angleLookA, glm::vec3 angleLookB);
	void addModelToCheck(Model* model);
	void drawPlanes();
};

#endif // !BSP_H
