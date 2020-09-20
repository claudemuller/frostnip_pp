#ifndef FROSTBYTE_ENTITYMANAGER_H
#define FROSTBYTE_ENTITYMANAGER_H

#include <vector>
#include "Entity.h"
#include "Component.h"
#include "CollisionEngine.h"

class EntityManager {
public:
	void clearData();
	void update(float deltaTime);
	void render();
	void destroyEntityAt(const int loc);
	bool hasEntities();
	Entity& addEntity(std::string name, LayerType layer);
	std::vector<Entity*> getEntities() const;
	Entity* getEntity(const std::string& entityId) const;
	std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
	unsigned int getEntityCount();
	void listEntities() const;
	CollisionType checkCollisions() const;

private:
	std::vector<Entity*> entities;
};

#endif //FROSTBYTE_ENTITYMANAGER_H
