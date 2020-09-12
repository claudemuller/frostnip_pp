#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(std::string tag, int x, int y, int width, int height) : tag(tag) {
	collider = {x, y, width, height};
}

void ColliderComponent::init() {
	if (owner->hasComponent<TransformComponent>()) {
		transform = owner->getComponent<TransformComponent>();
		srcRect = {0, 0, transform->width, transform->height};
		dstRect = {collider.x, collider.y, collider.w, collider.h};
	}
}

void ColliderComponent::update(float deltaTime) {
	collider.x = static_cast<int>(transform->position.getX());
	collider.y = static_cast<int>(transform->position.getY());
	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;
	dstRect.x = collider.x - Game::camera.x;
	dstRect.y = collider.y - Game::camera.y;
}

void ColliderComponent::render() {
	if (DEBUG) {
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(Game::renderer, &dstRect);
	}
}