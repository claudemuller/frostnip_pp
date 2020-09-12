#include <iostream>
#include "EntityManager.h"
#include "Constants.h"
#include "Collision.h"
#include "Components/ColliderComponent.h"

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
	for (int layerNum = 0; layerNum < NUM_LAYERS; layerNum++) {
		for (auto& entity : getEntitiesByLayer(static_cast<LayerType>(layerNum))) {
			entity->render();
		}
	}
}

bool EntityManager::hasEntities() {
	return !entities.empty();
}

Entity& EntityManager::addEntity(std::string name, LayerType layer) {
	Entity* entity = new Entity(*this, name, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const {
	return entities;
}

std::vector<Entity*> EntityManager::getEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities) {
		if (entity->layer == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

unsigned int EntityManager::getEntityCount() {
	return entities.size();
}

void EntityManager::listEntities() const {
	if (Game::debug) {
		unsigned int i = 0;
		for (auto& entity : entities) {
			std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
			entity->listComponents();
			i++;
		}
	}
}

std::string EntityManager::checkEntityCollisions(Entity& thisEntity) const {
	ColliderComponent* thisCollider = thisEntity.getComponent<ColliderComponent>();
	for (auto& entity : entities) {
		if (entity->name == thisEntity.name) {
			continue;
		}
		if (entity->hasComponent<ColliderComponent>() && entity->name != "tile") {
			ColliderComponent* thatCollider = entity->getComponent<ColliderComponent>();
			if (Collision::checkRectangleCollision(thisCollider->collider, thatCollider->collider)) {
				return thatCollider->tag;
			}
		}
	}
	return "";
}
