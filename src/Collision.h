#ifndef FROSTBYTE_COLLISION_H
#define FROSTBYTE_COLLISION_H

#include <SDL.h>

class Collision {
public:
	static bool checkRectangleCollision(const SDL_Rect& rectA, SDL_Rect& rectB);
};

#endif //FROSTBYTE_COLLISION_H
