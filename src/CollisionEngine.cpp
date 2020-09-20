#include "CollisionEngine.h"
#include "Components/ColliderComponent.h"
#include "Components/TextLabelComponent.h"

std::map<int, std::vector<Entity*>> CollisionEngine::mZones;
std::vector<Entity*> CollisionEngine::mMovingEntities;

void CollisionEngine::update() {
	// Check if entity still within its zone, otherwise move it to updated zone;
	std::cout << "number of zones that contain entities: " << mZones.size() << std::endl;
	std::cout << "number of entities in zone1: " << mZones.begin()->first << std::endl;
}

void CollisionEngine::render(EntityManager* entityManager) {
	if (Game::debug || true) {
		int zone = 0;
		for (int y = 0; y < WINDOW_WIDTH; y += COLLISION_ZONE_SIZE) {
			for (int x = 0; x < WINDOW_WIDTH; x += COLLISION_ZONE_SIZE) {
				SDL_Rect rect = {
						x,
						y,
						COLLISION_ZONE_SIZE,
						COLLISION_ZONE_SIZE
				};
				SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
				SDL_RenderDrawRect(Game::renderer, &rect);

				Entity& zoneNumber(entityManager->addEntity(std::to_string(zone), UI_LAYER));
				zoneNumber.addComponent<TextLabelComponent>(x + 10, y + 10, std::to_string(zone), "charriot-font", RED);
				zone++;
			}
		}
	}
}

CollisionType CollisionEngine::checkCollisions() {
	for (int i = 0; i < mMovingEntities.size(); i++) {
		Entity* thisEntity = mMovingEntities[i];
		for (auto* thatEntity : mMovingEntities) {
			if (thatEntity != thisEntity) {
				ColliderComponent* thisCollider = thisEntity->getComponent<ColliderComponent>();
				ColliderComponent* thatCollider = thatEntity->getComponent<ColliderComponent>();
				if (checkRectangleCollision(thisCollider->dstRect, thatCollider->dstRect)) {
					thisCollider->mHit = true;
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

				} else {
					thisCollider->mHit = false;
				}
			}
		}
	}
	return NO_COLLISION;
}

void CollisionEngine::addToMovingEntities(Entity* entity) {
	mMovingEntities.emplace_back(entity);
}

int CollisionEngine::addToZone(Entity* entity, SDL_Rect collider) {
	int col = collider.x / collider.w * COLLISION_ZONE_SIZE;
	int row = collider.y / collider.h * COLLISION_ZONE_SIZE;
	int loc = WINDOW_WIDTH * row + col;
	if (mZones.find(loc) == mZones.end()) {
		mZones.insert({loc, std::vector<Entity*>{entity}});
	} else {
		mZones[loc].emplace_back(entity);
	}
	return loc;
}

bool CollisionEngine::checkRectangleCollision(const SDL_Rect& rectA, SDL_Rect& rectB) {
	return (
			rectA.x + rectA.w >= rectB.x
			&& rectB.x + rectB.w >= rectA.x
			&& rectA.y + rectA.h >= rectB.y
			&& rectB.y + rectB.h >= rectA.y
	);
}

