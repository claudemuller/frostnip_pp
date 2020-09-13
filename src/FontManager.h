#ifndef FROSTBYTE_FONTMANAGER_H
#define FROSTBYTE_FONTMANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>

class FontManager {
public:
	static TTF_Font* loadFont(const char* filename, int fontSize);
	static void draw(SDL_Texture* texture, SDL_Rect position);
};

#endif //FROSTBYTE_FONTMANAGER_H
