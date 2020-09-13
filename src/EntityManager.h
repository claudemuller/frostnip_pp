#ifndef FROSTNIP_PP_ENTITYMANAGER_H
#define FROSTNIP_PP_ENTITYMANAGER_H

#include <vector>
#include "Entity.h"
#include "Component.h"

class EntityManager {
public:
	void clearData();
	void update(float deltaTime);
	void render();
	bool hasEntities();
	Entity& addEntity(std::string name, LayerType layer);
	std::vector<Entity*> getEntities() const;
	std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
	unsigned int getEntityCount();
	void listEntities() const;
	CollisionType checkCollisions() const;

private:
	std::vector<Entity*> entities;
};

#endif //FROSTNIP_PP_ENTITYMANAGER_H
