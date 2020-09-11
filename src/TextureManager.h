#ifndef FROSTNIP_PP_TEXTUREMANAGER_H
#define FROSTNIP_PP_TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* filename);
	static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip);
};

#endif //FROSTNIP_PP_TEXTUREMANAGER_H
