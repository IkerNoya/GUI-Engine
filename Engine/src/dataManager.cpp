#include "dataManager.h"
#include <iostream>
#include <mutex>

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
			if (levelEntities[i]->getID() == id) {
				if(entity->getName() != "")
					std::cout << entity->getName() << " - has already been saved" << std::endl;
				else
					std::cout << "NULL Entity - has already been saved" << std::endl;

				return;
			}
		}
		entity->setID(id);
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

Entity* DataManager::getSelectedEntity() {
	return selectedEntity;
}