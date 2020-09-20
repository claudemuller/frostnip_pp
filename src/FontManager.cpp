#include "FontManager.h"
#include "Game.h"
#include "Utils/Vec2.h"

TTF_Font* FontManager::loadFont(const char* filename, int fontSize) {
	return TTF_OpenFont(filename, fontSize);
}

void FontManager::draw(SDL_Texture* texture, SDL_Rect position) {
	SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}
