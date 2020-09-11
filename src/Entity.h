#ifndef FROSTNIP_PP_ENTITY_H
#define FROSTNIP_PP_ENTITY_H

#include <vector>
#include <string>
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

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		newComponent->init();
		return *newComponent;
	}

private:
	EntityManager& manager;
	bool active;
	std::vector<Component*> components;
};

#endif //FROSTNIP_PP_ENTITY_H
