#include "TileComponent.h"
#include "../EntityManager.h"
#include "../AssetManager.h"

TileComponent::TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId) {
	texture = Game::assetManager->getTexture(assetTextureId);

	srcRect.x = srcRectX;
	srcRect.y = srcRectY;
	srcRect.w = tileSize;
	srcRect.h = tileSize;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = tileSize * tileScale;
	dstRect.h = tileSize * tileScale;

	position.setX(x);
	position.setY(y);
}

TileComponent::~TileComponent() {
	SDL_DestroyTexture(texture);
}

void TileComponent::update(float deltaTime) {
	dstRect.x = position.getX() - Game::camera.x;
	dstRect.y = position.getY() - Game::camera.y;
}

void TileComponent::render() {
	TextureManager::draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
}
