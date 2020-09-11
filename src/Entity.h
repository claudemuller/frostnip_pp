#ifndef FROSTNIP_PP_ENTITY_H
#define FROSTNIP_PP_ENTITY_H

#include <vector>
#include <string>
#include "EntityManager.h"
#include "Component.h"

class EntityManager;
class Component;

class Entity {
public:
	std::string name;

	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name);

	void update(float deltaTime);
	void render();
	void destroy();
	bool isActive() const { return active; };

private:
	EntityManager& manager;
	bool active;
	std::vector<Component*> components;
};

#endif //FROSTNIP_PP_ENTITY_H
