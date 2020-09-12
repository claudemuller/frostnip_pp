#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char* assetTextureId) {
	setTexture(assetTextureId);
}
void SpriteComponent::init() {
	transform = owner->getComponent<TransformComponent>();
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = transform->width;
	srcRect.h = transform->height;
}

void SpriteComponent::update(float deltaTime) {
	dstRect.x = (int)transform->position.getX();
	dstRect.y = (int)transform->position.getY();
	dstRect.w = transform->width * transform->scale;
	dstRect.h = transform->height * transform->scale;
}

void SpriteComponent::render() {
	TextureManager::draw(texture, srcRect, dstRect, spriteFlip);
}

void SpriteComponent::setTexture(std::string assetTextureId) {
	texture = Game::assetManager->getTexture(assetTextureId);
}
