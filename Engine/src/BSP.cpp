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
	bool checkPassed = true;
	std::cout << std::endl;

	if (mesh->IsParent()) {
		for (int i = 0; i < _planes.size(); i++) {
			glm::vec3 dirA = glm::normalize(mesh->GetMinCollGeneral() - _planes[i].model->transform.position);
			float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);

			glm::vec3 dirB = glm::normalize(mesh->GetMaxCollGeneral() - _planes[i].model->transform.position);
			float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);

			if (dotProdA < 0.0f && dotProdB < 0.0f) {
				std::cout << "mesh : " << mesh->GetName() << " dont pass general check!" << std::endl;
				checkPassed = false;
				break;
			}
		}

		if (!checkPassed) {
			mesh->show(false);
			return;
		}
		else
			std::cout << "mesh: " << mesh->GetName() << " pass general check!" << std::endl;
	}
	else
		std::cout << "mesh : " << mesh->GetName() << " has 0 sons, dont make general check!" << std::endl;


	for (int i = 0; i < _planes.size(); i++) {
		glm::vec3 dirA = glm::normalize(mesh->GetMinColl() - _planes[i].model->transform.position);
		float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);

		glm::vec3 dirB = glm::normalize(mesh->GetMaxColl() - _planes[i].model->transform.position);
		float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);

		if (dotProdA < 0.0f && dotProdB < 0.0f) {
			checkPassed = false;
			break;
		}
	}

	if (!checkPassed) {
		mesh->show(false);
		std::cout << "mesh: " << mesh->GetName() << " dont pass own check!" << std::endl;
	}
	else {
		mesh->show(true);
		std::cout << "mesh: " << mesh->GetName() << " pass own check!" << std::endl;
	}



	for (int i = 0; i < mesh->getChildren().size(); i++)
		checkObject(((Mesh*)mesh->getChildren()[i]));

}

void BSP::checkPlaneCamera(Entity* camera)
{
	std::cout << "camera transform pos x: " << camera->transform.position.x << " y: " << camera->transform.position.y << " z: " << camera->transform.position.z << std::endl;
	for (int i = 0; i < _planes.size(); i++) {

		std::cout << _planes[i].model->GetName() << " transform pos x : " << _planes[i].model->transform.position.x << " y : " << _planes[i].model->transform.position.y << " z : " << _planes[i].model->transform.position.z << std::endl;

		glm::vec3 dirFromAtoB = glm::normalize(camera->transform.position - _planes[i].model->transform.position);
		float dotProd = glm::dot(dirFromAtoB, _planes[i].model->transform.forward);

		std::cout << _planes[i].model->GetName() << " dot prod: " << dotProd << std::endl;
		if (dotProd < 0) {
			glm::vec3 rot;
			if (_planes[i].model->transform.rotation == _planes[i].angleLookA)
				rot = _planes[i].angleLookB;
			else
				rot = _planes[i].angleLookA;

			_planes[i].model->transform.rotation = glm::vec3(rot.x, rot.y, rot.z);
			std::cout << "plane " << i << " rotated" << std::endl;
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
