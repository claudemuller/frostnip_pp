#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char* assetTextureId) {
	animated = false;
	fixed = false;
	setTexture(assetTextureId);
}

SpriteComponent::SpriteComponent(const char* assetTextureId, int numFrames, int animationSpeed, bool hasDirections, bool isFixed)
		: numFrames(numFrames), animationSpeed(animationSpeed), fixed(isFixed) {
	animated = true;
	if (hasDirections) {
		Animation downAnimation = Animation(0, numFrames, animationSpeed);
		Animation rightAnimation = Animation(1, numFrames, animationSpeed);
		Animation leftAnimation = Animation(2, numFrames, animationSpeed);
		Animation upAnimation = Animation(3, numFrames, animationSpeed);
		animations.emplace("DownAnimation", downAnimation);
		animations.emplace("RightAnimation", rightAnimation);
		animations.emplace("LeftAnimation", leftAnimation);
		animations.emplace("UpAnimation", upAnimation);
		animationIndex = 0;
		currentAnimationName = "DownAnimation";
	} else {
		Animation singleAnimation = Animation(0, numFrames, animationSpeed);
		currentAnimationName = "SingleAnimation";
		animationIndex = 0;
		animations.emplace(currentAnimationName, singleAnimation);
	}

	play(currentAnimationName);
	setTexture(assetTextureId);
}

void SpriteComponent::init() {
	transform = owner->getComponent<TransformComponent>();
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = transform->width;
	srcRect.h = transform->height;
}

void SpriteComponent::play(std::string name) {
	numFrames = animations[name].numFrames;
	animationIndex = animations[name].index;
	animationSpeed = animations[name].speed;
	currentAnimationName = name;
}

void SpriteComponent::update(float deltaTime) {
	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
	}
	srcRect.y = animationIndex * transform->height;

	dstRect.x = static_cast<int>(transform->position.getX()) - (fixed ? 0 : Game::camera.x);
	dstRect.y = static_cast<int>(transform->position.getY()) - (fixed ? 0 : Game::camera.y);
	dstRect.w = transform->width * transform->scale;
	dstRect.h = transform->height * transform->scale;
}

void SpriteComponent::render() {
	TextureManager::draw(texture, srcRect, dstRect, spriteFlip);
}

void SpriteComponent::setTexture(std::string assetTextureId) {
	texture = Game::assetManager->getTexture(assetTextureId);
}
