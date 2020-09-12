#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* filename) {
	SDL_Surface* surface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	if (texture == nullptr) {
		std::cerr << "Error loading texture file " << filename << std::endl;
	}
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &dstRect, 0.0, NULL, flip);
}
