#include "dataManager.h"

DataManager::DataManager() {
	
}

DataManager::~DataManager() {
	if (levelEntities.size() > 0) {
		levelEntities.clear();
	}
}

void DataManager::addEntity(Entity* entity, int id) {
	if (entity != NULL){
		for (int i = 0; i < levelEntities.size(); i++) {
			if (levelEntities[i]->getID() == id) {
				std::cout << entity->getName() << " - has already been saved" << std::endl;
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
