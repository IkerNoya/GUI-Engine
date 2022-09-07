#include "AABB.h"
#include "../debug.h"

AABB::AABB() : Entity() {

}

AABB::~AABB() {
}

void AABB::attachToEntity(ModelMatrix model, Transform transformAttached) {
	modelMatrix = model;
	transform = transformAttached;
	updateSelfAndChild();
}

void AABB::updateModel(ModelMatrix model, Transform transformAttached) {
	modelMatrix = model;
	transform = transformAttached;
	updateSelfAndChild();
}

void AABB::draw(Line* line) {
	//if (verticesPositions.size() <= 0) return;
	//std::vector<int> edges = { 0,1, 1,2, 2,3, 3,0, 4,5, 5,6, 6,7, 7,4, 1,5, 2,6, 3,7, 0,4 };
	//for (int i = 0; i < edges.size(); i++) {
	//	if(line)
	//		if(i+1< edges.size())
	//			line->draw(verticesPositions[edges[i]], verticesPositions[edges[i+1]], glm::vec3(0,1,0));
	//		else
	//			line->draw(verticesPositions[edges[i]], verticesPositions[edges[0]], glm::vec3(0,1,0));
	//}
}
