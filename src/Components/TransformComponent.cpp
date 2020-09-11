#include "SDL.h"
#include "TransformComponent.h"
#include "../Game.h"

TransformComponent::TransformComponent(int x, int y, int velX, int velY, int w, int h, int s) {
	position = Vec2(x, y);
	velocity = Vec2(velX, velY);
	width = w;
	height = h;
	scale = s;
}

void TransformComponent::init() {
}

void TransformComponent::update(float deltaTime) {
	position += velocity * deltaTime;
}

void TransformComponent::render() {
	SDL_Rect transformRect = {
			(int)position.getX(),
			(int)position.getY(),
			width,
			height
	};
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::renderer, &transformRect);
}
