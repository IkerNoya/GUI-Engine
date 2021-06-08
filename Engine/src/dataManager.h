#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "export.h"
#include "entity.h"
#include <list>
#include <vector>

class ENGINE_API DataManager {
	std::vector<Entity*> levelEntities;
	Entity* selectedEntity;
public:
	DataManager();
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

