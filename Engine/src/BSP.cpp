#include "BSP.h"

BSP::BSP(Shader& shader)
{
	_shader = shader;
	_models.clear();
	_planes.clear();
}

BSP::~BSP()
{
	_models.clear();
	_planes.clear();
}

void BSP::check()
{
	for (auto* model : _models) {
		checkObject(model->GetMeshes()[0]);
	}
}

void BSP::checkObject(Mesh* mesh)
{
	bool isInCorrectSide = true;
	//if (mesh->getParent()) {
	//	for (int i = 0; i < _planes.size(); i++) {
	//		glm::vec3 dirA = glm::normalize(mesh->GetMinCollGeneral() - _planes[i].model->transform.position);
	//		float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);

	//		glm::vec3 dirB = glm::normalize(mesh->GetMaxCollGeneral() - _planes[i].model->transform.position);
	//		float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);

	//		if (dotProdA < 0.0f && dotProdB < 0.0f) {
	//			std::cout << "mesh : " << mesh->GetName() << " dont pass general check!" << std::endl;
	//			isInCorrectSide = false;
	//			break;
	//		}
	//	}
	//}
}

void BSP::checkPlaneCamera(Entity* camera)
{
}

void BSP::addPlane(Model* model, glm::vec3 angleLookA, glm::vec3 angleLookB)
{
}

void BSP::addModelToCheck(Model* model)
{
}

void BSP::drawPlanes()
{
}
