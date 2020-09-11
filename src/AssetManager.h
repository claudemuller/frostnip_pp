#ifndef FROSTNIP_PP_ASSETMANAGER_H
#define FROSTNIP_PP_ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "EntityManager.h"

class AssetManager {
public:
	AssetManager(EntityManager* manager);

	void clearData();
	void addTexture(std::string textureId, const char* filename);
	SDL_Texture* getTexture(std::string textureId);

private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
};

#endif //FROSTNIP_PP_ASSETMANAGER_H
