#ifndef FROSTBYTE_ASSETMANAGER_H
#define FROSTBYTE_ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"

class AssetManager {
public:
	AssetManager(EntityManager* manager);

	void clearData();
	void addTexture(const std::string& textureId, const char* filename);
	SDL_Texture* getTexture(const std::string& textureId);
	void addFont(const std::string& fontId, const char* filename, int fontSize);
	TTF_Font* getFont(const std::string& fontId);

private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font *> fonts;
};

#endif //FROSTBYTE_ASSETMANAGER_H
