#ifndef FROSTBYTE_MOUSECONTROLCONTROLLER_H
#define FROSTBYTE_MOUSECONTROLCONTROLLER_H

#include <SDL.h>
#include "Utils/Vec2.h"

class Camera : public SDL_Rect {
public:
	Camera();

	void update(float deltaTime);

private:
	Vec2 mMouseLastLoc;
};

#endif //FROSTBYTE_MOUSECONTROLCONTROLLER_H
