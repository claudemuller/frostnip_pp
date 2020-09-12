#ifndef FROSTNIP_PP_ENTITY_H
#define FROSTNIP_PP_ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "Constants.h"
#include "Component.h"

class EntityManager;

class Component;

class Entity {
public:
	std::string name;
	LayerType layer;

	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name, LayerType layer);

	void update(float deltaTime);
	void render();
	void destroy();
	bool isActive() const { return active; };
	void listComponents();

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&& ... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		componentTypeMap[&typeid(*newComponent)] = newComponent;
		newComponent->init();
		return *newComponent;
	}

	template<typename T>
	bool hasComponent() const {
		return componentTypeMap.count(&typeid(T));
	}

	template<typename T>
	T* getComponent() {
		return static_cast<T*>(componentTypeMap[&typeid(T)]);
	}

private:
	EntityManager& manager;
	int speed;
	bool active;
	std::vector<Component*> components;
	std::map<const std::type_info*, Component*> componentTypeMap;
};

#endif //FROSTNIP_PP_ENTITY_H
