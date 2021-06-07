#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "export.h"
#include "entity.h"
#include <list>
#include <vector>

class ENGINE_API DataManager {
	std::vector<Entity*> levelEntities;
public:
	DataManager();
	~DataManager();
	void addEntity(Entity* entity, int id);
	void saveEntities();
	void loadEntities();
	void clearLevelEntities();
	std::vector<Entity*> getLevelEntities();
};


#endif // !DATAMANAGER_H

