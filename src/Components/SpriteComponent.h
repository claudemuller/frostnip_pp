#ifndef FROSTNIP_PP_SPRITECOMPONENT_H
#define FROSTNIP_PP_SPRITECOMPONENT_H

#include "SDL.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(const char* filename);

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void setTexture(std::string assetTextureId);

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
};

#endif //FROSTNIP_PP_SPRITECOMPONENT_H
