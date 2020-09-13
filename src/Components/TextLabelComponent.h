#ifndef FROSTNIP_PP_TEXTLABELCOMPONENT_H
#define FROSTNIP_PP_TEXTLABELCOMPONENT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"

class TextLabelComponent : public Component {
public:
	TextLabelComponent(int x, int y, std::string text, std::string fontFamily, SDL_Color colour);

	void setLabelText(std::string text, std::string fontId);
	void render() override;

private:
	SDL_Rect position;
	std::string text;
	std::string fontFamily;
	SDL_Color colour;
	SDL_Texture* texture;
};

#endif //FROSTNIP_PP_TEXTLABELCOMPONENT_H
