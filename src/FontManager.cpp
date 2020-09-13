#include "FontManager.h"
#include "Game.h"

TTF_Font* FontManager::loadFont(const char* filename, int fontSize) {
	return TTF_OpenFont(filename, fontSize);
}

void FontManager::draw(SDL_Texture* texture, SDL_Rect position) {
	SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}
