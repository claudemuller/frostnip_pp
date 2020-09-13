#ifndef FROSTBYTE_TILECOMPONENT_H
#define FROSTBYTE_TILECOMPONENT_H

#include <SDL.h>
#include "../Utils/Vec2.h"
#include "../Component.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	Vec2 position;

	TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId);
	~TileComponent();

	void update(float deltaTime) override;
	void render() override;
};

#endif //FROSTBYTE_TILECOMPONENT_H
