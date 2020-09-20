#include <iostream>
#include "EntityManager.h"
#include "Constants.h"
#include "Components/ColliderComponent.h"

void EntityManager::clearData() {
	for (auto& entity : entities) {
		entity->destroy();
	}
}

void EntityManager::update(float deltaTime) {
	for (int i = 0; i < entities.size(); i++) {
		Entity* entity = entities[i];
		if (entity->isActive()) {
			entity->update(deltaTime);
		} else {
			destroyEntityAt(i);
		}
	}
}

void EntityManager::render() {
	for (int layerNum = 0; layerNum < NUM_LAYERS; layerNum++) {
		for (auto& entity : getEntitiesByLayer(static_cast<LayerType>(layerNum))) {
			entity->render();
		}
	}
}

void EntityManager::destroyEntityAt(const int loc) {
	entities.erase(entities.begin() + loc);
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

Entity* EntityManager::getEntity(const std::string& entityId) const {
	for (auto& entity : entities) {
		if (entity->name == entityId) {
			return entity;
		}
	}
	return NULL;
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

// TODO: better collision here.
CollisionType EntityManager::checkCollisions() const {
	for (auto& thisEntity : entities) {
		if (thisEntity->hasComponent<ColliderComponent>()) {

			ColliderComponent* thisCollider = thisEntity->getComponent<ColliderComponent>();
			for (auto& thatEntity : entities) {
				if (thisEntity->name != thatEntity->name && thatEntity->hasComponent<ColliderComponent>()) {

					ColliderComponent* thatCollider = thatEntity->getComponent<ColliderComponent>();
					if (CollisionEngine::checkRectangleCollision(thisCollider->collider, thatCollider->collider)) {

						if (thisCollider->tag == "player" && thatCollider->tag == "enemy") {
							return PLAYER_ENEMY_COLLISION;
						}

						if (thisCollider->tag == "player" && thatCollider->tag == "projectile") {
							return PLAYER_PROJECTILE_COLLISION;
						}

						if (thisCollider->tag == "player" && thatCollider->tag == "level_complete") {
							return PLAYER_LEVEL_COMPLETE_COLLISION;
						}

						if (thisCollider->tag == "enemy" && thatCollider->tag == "friendly_projectile") {
							return ENEMY_PROJECTILE_COLLISION;
						}

					}

				}
			}

		}
	}
	return NO_COLLISION;
}
