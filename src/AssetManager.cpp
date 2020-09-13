#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager) : manager(manager) {
}

void AssetManager::clearData() {
	textures.clear();
	fonts.clear();
}

void AssetManager::addTexture(const std::string& textureId, const char* filename) {
	textures.emplace(textureId, TextureManager::loadTexture(filename));
}

SDL_Texture* AssetManager::getTexture(const std::string& textureId) {
	return textures[textureId];
}

void AssetManager::addFont(const std::string& fontId, const char* filename, int fontSize) {
	fonts.emplace(fontId, FontManager::loadFont(filename, fontSize));
}

TTF_Font* AssetManager::getFont(const std::string& fontId) {
	return fonts[fontId];
}
