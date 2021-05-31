#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "export.h"
#include "entity.h"
#include <list>
#include <vector>

class ENGINE_API DataManager {
	std::list<Entity*> levelEntities;
public:
	DataManager();
	~DataManager();
	void addEntity(Entity* entity);
	void saveEntities();
	void loadEntities();
	void clearLevelEntities();
};


#endif // !DATAMANAGER_H

