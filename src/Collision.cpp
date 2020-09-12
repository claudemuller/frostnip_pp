#include "Collision.h"

bool Collision::checkRectangleCollision(const SDL_Rect& rectA, SDL_Rect& rectB) {
	return (
			rectA.x + rectA.w >= rectB.x
			&& rectB.x + rectB.w >= rectA.x
			&& rectA.y + rectA.h >= rectB.y
			&& rectB.y + rectB.h >= rectA.y
	);
}

