#ifndef FROSTNIP_PP_FONTMANAGER_H
#define FROSTNIP_PP_FONTMANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>

class FontManager {
public:
	static TTF_Font* loadFont(const char* filename, int fontSize);
	static void draw(SDL_Texture* texture, SDL_Rect position);
};

#endif //FROSTNIP_PP_FONTMANAGER_H
