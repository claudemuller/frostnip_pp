#ifndef FROSTBYTE_COLLISIONENGINE_H
#define FROSTBYTE_COLLISIONENGINE_H

#include "Entity.h"

const int COLLISION_ZONE_SIZE = 9 * 32;

enum CollisionType {
	NO_COLLISION,
	PLAYER_ENEMY_COLLISION,
	PLAYER_PROJECTILE_COLLISION,
	ENEMY_PROJECTILE_COLLISION,
	PLAYER_VEGETATION_COLLISION,
	PLAYER_LEVEL_COMPLETE_COLLISION
};

class CollisionEngine {
public:
	static void init();
	static void update();
	static void render();
	static CollisionType checkCollisions();
	static void addToMovingEntities(Entity* entity);
	static int addToZone(Entity* entity, SDL_Rect collider);
	static bool checkRectangleCollision(const SDL_Rect& rectA, SDL_Rect& rectB);

private:
	static Entity* mZoneNumber;
	static std::map<int, std::vector<Entity*>> mZones;
	static std::vector<Entity*> mMovingEntities;
	static SDL_Rect mDebugRect;
};

#endif //FROSTBYTE_COLLISIONENGINE_H
