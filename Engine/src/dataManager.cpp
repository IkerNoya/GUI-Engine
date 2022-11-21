#include "dataManager.h"
#include <iostream>
#include <mutex>
#include <string>
#include <algorithm>

DataManager* DataManager::_instance = nullptr;

DataManager* DataManager::Get() {
	if (_instance == NULL) {
		_instance = new DataManager();
	}
	return _instance;
}

DataManager::~DataManager() {
	if (!levelEntities.empty()) {
		levelEntities.clear();
	}
}

void DataManager::addEntity(Entity* entity, int id) {
	if (entity != NULL){
		for (int i = 0; i < levelEntities.size(); i++) {
			if (levelEntities[i]->GetID() == id) {
				if(entity->GetName() != "")
					std::cout << entity->GetName() << " - has already been saved" << std::endl;
				else
					std::cout << "NULL Entity - has already been saved" << std::endl;

				return;
			}
		}
		entity->SetID(id);
		levelEntities.push_back(entity);
	}
}

void DataManager::saveEntities() {
	std::cout << "SAVING" << std::endl;
}

void DataManager::loadEntities() {
	std::cout << "LOADING" << std::endl;

}

void DataManager::clearLevelEntities() {
	levelEntities.clear();
}

std::vector<Entity*> DataManager::getLevelEntities() {
	return levelEntities;
}

void DataManager::setSelectedEntity(Entity* entity) {
	selectedEntity = entity;
}

Entity* DataManager::GetEntityWithName(const char* name)
{
	for (auto* entity : levelEntities) {
		if (entity->GetName() == name) {
			return entity;
		}
	}
	return nullptr;
}

bool DataManager::TryGetEntityFromPrefix(const char* name, std::vector<Entity*>& entities)
{

	std::string planeSufix = name;

	for (auto* entity : levelEntities)
	{
		std::string entityName = entity->GetName();
		auto res = std::mismatch(planeSufix.begin(), planeSufix.end(), entityName.begin());
		if (res.first == planeSufix.end()) {
			entities.push_back(entity);
		}
	}
	if (entities.size() > 0)
		return true;

	return false ;
}

Entity* DataManager::getSelectedEntity() {
	return selectedEntity;
}