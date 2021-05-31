#include "dataManager.h"

DataManager::DataManager() {
	
}

DataManager::~DataManager() {
	if (levelEntities.size() > 0) {
		levelEntities.clear();
	}
}

void DataManager::addEntity(Entity* entity) {
	if (entity != NULL){
		levelEntities.push_back(entity);
		for (int i = 0; i < levelEntities.size(); i++) {
			std::cout << i << std::endl;
		}
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
