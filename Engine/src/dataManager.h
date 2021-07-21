#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "export.h"
#include "entity.h"
#include <list>
#include <vector>

class ENGINE_API DataManager {
private: 
	std::vector<Entity*> levelEntities;
	Entity* selectedEntity;
	DataManager() { selectedEntity = nullptr; }
	static DataManager* ptr;

public:
	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;
	static DataManager* Get();
	~DataManager();
	void addEntity(Entity* entity, int id);
	void saveEntities();
	void loadEntities();
	void clearLevelEntities();
	std::vector<Entity*> getLevelEntities();
	Entity* getSelectedEntity();
	void setSelectedEntity(Entity* entity);
}; 


#endif // !DATAMANAGER_H

