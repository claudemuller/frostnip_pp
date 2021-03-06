#ifndef FROSTBYTE_TEXTLABELCOMPONENT_H
#define FROSTBYTE_TEXTLABELCOMPONENT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"
#include "../Utils/Vec2.h"

class TextLabelComponent : public Component {
public:
	TextLabelComponent(int x, int y, std::string text, std::string fontFamily, SDL_Color colour);

	void setLabelText(std::string text, std::string fontId);
	void update(float deltaTime) override;
	void render() override;

private:
	SDL_Rect position;
	std::string text;
	std::string fontFamily;
	SDL_Color colour;
	SDL_Texture* texture;
};

#endif //FROSTBYTE_TEXTLABELCOMPONENT_H
