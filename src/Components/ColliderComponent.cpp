#include "ColliderComponent.h"
#include "TextLabelComponent.h"

extern EntityManager entityManager;

ColliderComponent::ColliderComponent(std::string tag, int x, int y, int width, int height) : tag(tag) {
	collider = {x, y, width, height};
}

void ColliderComponent::init() {
	if (owner->hasComponent<TransformComponent>()) {
		transform = owner->getComponent<TransformComponent>();
		if (transform != nullptr) {
			// If it moves, add it to the "to check" entities.
			CollisionEngine::addToMovingEntities(owner);
		}
		srcRect = {0, 0, transform->width, transform->height};
		dstRect = {collider.x, collider.y, collider.w, collider.h};
		// Add to collision zone if has collider.
		mZoneNumber = CollisionEngine::addToZone(owner, dstRect);

		Entity& zoneNumberEntity = entityManager.addEntity(std::to_string(mZoneNumber), UI_LAYER);
		zoneNumberEntity.addComponent<TransformComponent>(
				transform->position.getX(),
				transform->position.getY(),
				transform->velocity.getX(),
				transform->velocity.getY(),
				transform->width,
				transform->height,
				transform->scale
				);
		zoneNumberEntity.addComponent<TextLabelComponent>(
				collider.x + 10,
				collider.y + 10,
				std::to_string(mZoneNumber),
				"charriot-font",
				RED
		);
	}
}

void ColliderComponent::update(float deltaTime) {
	collider.x = static_cast<int>(transform->position.getX());
	collider.y = static_cast<int>(transform->position.getY());
	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;
	dstRect.x = collider.x - Game::camera.x;
	dstRect.y = collider.y - Game::camera.y;

	Entity* zoneLabel = entityManager.getEntity(std::to_string(mZoneNumber));
	TransformComponent* zoneTransform = zoneLabel->getComponent<TransformComponent>();
	zoneTransform->position.setX(dstRect.x);
	zoneTransform->position.setY(dstRect.y);
}

void ColliderComponent::render() {
	if (Game::debug || mHit) {
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(Game::renderer, &dstRect);
	}
}