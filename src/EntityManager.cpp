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

// TODO: better collision here.
CollisionType EntityManager::checkCollisions() const {
	for (auto& thisEntity : entities) {
		if (thisEntity->hasComponent<ColliderComponent>()) {

			ColliderComponent* thisCollider = thisEntity->getComponent<ColliderComponent>();
			for (auto& thatEntity : entities) {
				if (thisEntity->name != thatEntity->name && thatEntity->hasComponent<ColliderComponent>()) {

					ColliderComponent* thatCollider = thatEntity->getComponent<ColliderComponent>();
					if (Collision::checkRectangleCollision(thisCollider->collider, thatCollider->collider)) {

						if (thisCollider->tag == "PLAYER" && thatCollider->tag == "ENEMY") {
							return PLAYER_ENEMY_COLLISION;
						}

						if (thisCollider->tag == "PLAYER" && thatCollider->tag == "PROJECTILE") {
							return PLAYER_PROJECTILE_COLLISION;
						}

						if (thisCollider->tag == "PLAYER" && thatCollider->tag == "LEVEL_COMPLETE") {
							return PLAYER_LEVEL_COMPLETE_COLLISION;
						}

						if (thisCollider->tag == "ENEMY" && thatCollider->tag == "FRIENDLY_PROJECTILE") {
							return ENEMY_PROJECTILE_COLLISION;
						}

					}

				}
			}

		}
	}
	return NO_COLLISION;
}
