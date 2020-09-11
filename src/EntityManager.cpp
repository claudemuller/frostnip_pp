#include "EntityManager.h"

void EntityManager::clearData() {
	for (auto& entity : entities) {
		entity->destroy();
	}
}

void EntityManager::update(float deltaTime) {
	for (auto& entity : entities) {
		entity->update(deltaTime);
	}
}

void EntityManager::render() {
	for (auto& entity : entities) {
		entity->render();
	}
}

bool EntityManager::hasEntities() {
	return !entities.empty();
}

Entity& EntityManager::addEntity(std::string name) {
	Entity* entity = new Entity(*this, name);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const {
	return entities;
}

unsigned int EntityManager::getEntityCount() {
	return entities.size();
}