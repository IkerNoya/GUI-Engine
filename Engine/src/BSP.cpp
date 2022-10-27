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
		checkObject(model->GetMeshes()[0], true);
	}
}

void BSP::checkObject(Mesh* mesh, bool isRoot)
{
	if (!isRoot)
	{
		bool checkPassed = true;
		std::cout << std::endl;

		if (mesh->IsParent()) {
			for (int i = 0; i < _planes.size(); i++) {
				glm::vec3 dirA = glm::normalize(mesh->GetMinCollGeneral() - _planes[i].model->transform.position);
				float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);

				glm::vec3 dirB = glm::normalize(mesh->GetMaxCollGeneral() - _planes[i].model->transform.position);
				float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);

				if (dotProdA < 0.0f && dotProdB < 0.0f) {
					checkPassed = false;
					break;
				}
			}

			if (!checkPassed) {
				mesh->show(false);
				return;
			}
		}


		for (int i = 0; i < _planes.size(); i++) {
			glm::vec3 dirA = glm::normalize(mesh->GetMinColl() - _planes[i].model->transform.position);
			float dotProdA = glm::dot(dirA, _planes[i].model->getForward());

			glm::vec3 dirB = glm::normalize(mesh->GetMaxColl() - _planes[i].model->transform.position);
			float dotProdB = glm::dot(dirB, _planes[i].model->getForward());

			if (dotProdA < 0.0f && dotProdB < 0.0f) {
				checkPassed = false;
				break;
			}
		}

		if (!checkPassed) {
			mesh->show(false);
		}
		else {
			mesh->show(true);
		}
	}
	for (int i = 0; i < mesh->getChildren().size(); i++)
		checkObject(((Mesh*)mesh->getChildren()[i]), false);

}

void BSP::checkPlaneCamera(Entity* camera)
{
	for (int i = 0; i < _planes.size(); i++) {


		glm::vec3 dirFromAtoB = glm::normalize(camera->transform.position - _planes[i].model->transform.position);
		float dotProd = glm::dot(dirFromAtoB, _planes[i].model->getForward());

		if (dotProd < 0) {
			glm::vec3 rot;
			if (_planes[i].model->transform.rotation == _planes[i].angleLookA)
				rot = _planes[i].angleLookB;
			else
				rot = _planes[i].angleLookA;

			_planes[i].model->transform.rotation = glm::vec3(rot.x, rot.y, rot.z);
		}
	}
}

void BSP::addPlane(Model* model, glm::vec3 angleLookA, glm::vec3 angleLookB)
{
	BSPlane plane;
	plane.model = model;
	plane.angleLookA = angleLookA;
	plane.angleLookB = angleLookB;
	_planes.push_back(plane);
}

void BSP::addModelToCheck(Model* model)
{
	_models.push_back(model);
}

void BSP::drawPlanes()
{
	for (int i = 0; i < _planes.size(); i++)
		if (_planes[i].model != NULL)
			_planes[i].model->draw(nullptr);
}
