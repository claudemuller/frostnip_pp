#include <iostream>
#include <SDL.h>
#include "Camera.h"
#include "Game.h"
#include "Components/TransformComponent.h"

extern EntityManager entityManager;

Camera::Camera() {
	x = 0;
	y = 0;
	w = WINDOW_WIDTH;
	h = WINDOW_HEIGHT;
	mMouseLastLoc = Vec2(0, 0);
}

void Camera::update(float deltaTime) {
	if (Game::event.type == SDL_MOUSEMOTION) {
		Sint32 mouseX = Game::event.motion.x;
		Sint32 mouseY = Game::event.motion.y;

		SDL_PumpEvents();
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
			x += -1 * (mouseX - mMouseLastLoc.getX());
			y += -1 * (mouseY - mMouseLastLoc.getY());
		}
		mMouseLastLoc = Vec2(mouseX, mouseY);
	}

	Entity* player = entityManager.getEntity("player");
	if (player != nullptr) {
		TransformComponent* playerTransform = player->getComponent<TransformComponent>();

		x = playerTransform->position.getX() - (WINDOW_WIDTH / 2);
		x = x < 0 ? 0 : x;
		x = x > WINDOW_WIDTH ? WINDOW_WIDTH : x;

		y = playerTransform->position.getY() - (WINDOW_WIDTH / 2);
		y = y < 0 ? 0 : y;
		y = y > WINDOW_HEIGHT ? WINDOW_HEIGHT : y;
	}
}
