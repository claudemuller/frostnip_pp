#ifndef FROSTBYTE_SPRITECOMPONENT_H
#define FROSTBYTE_SPRITECOMPONENT_H

#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "TransformComponent.h"
#include "../Animation.h"

class SpriteComponent : public Component {
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(const char* filename);
	SpriteComponent(const char* assetTextureId, int numFrames, int animationSpeed, bool hasDirections, bool isFixed);

	void init() override;
	void play(std::string name);
	void update(float deltaTime) override;
	void render() override;
	void setTexture(std::string assetTextureId);

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	bool animated;
	int numFrames;
	int animationSpeed;
	bool fixed;
	std::map<std::string, Animation> animations;
	std::string currentAnimationName;
	unsigned int animationIndex = 0;
};

#endif //FROSTBYTE_SPRITECOMPONENT_H
