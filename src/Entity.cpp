#include <iostream>
#include "Entity.h"

Entity::Entity(EntityManager& manager) : manager(manager) {
	active = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer) : manager(manager), name(name), layer(layer) {
	active = true;
}

void Entity::update(float deltaTime) {
	for (auto& component : components) {
		component->update(deltaTime);
	}
}

void Entity::render() {
	for (auto& component : components) {
		component->render();
	}
}

void Entity::destroy() {
	active = false;
}

void Entity::listComponents() {
	unsigned int i = 0;
	for (auto& componentType : componentTypeMap) {
		std::cout << "\t|_Component<" << componentType.first->name() << ">" << std::endl;
		i++;
	}
}

