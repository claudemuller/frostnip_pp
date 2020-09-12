#ifndef FROSTNIP_PP_COLLISION_H
#define FROSTNIP_PP_COLLISION_H

#include "SDL.h"

class Collision {
public:
	static bool checkRectangleCollision(const SDL_Rect& rectA, SDL_Rect& rectB);
};

#endif //FROSTNIP_PP_COLLISION_H
