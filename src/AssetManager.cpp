#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager) : manager(manager) {
}

void AssetManager::clearData() {
	textures.clear();
}

void AssetManager::addTexture(std::string textureId, const char* filename) {
	textures.emplace(textureId, TextureManager::loadTexture(filename));
}

SDL_Texture* AssetManager::getTexture(std::string textureId) {
	return textures[textureId];
}
