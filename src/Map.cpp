#include <fstream>
#include "Map.h"
#include "EntityManager.h"
#include "Components/TileComponent.h"

extern EntityManager entityManager;

Map::Map(std::string textureId, int scale, int tileSize) : textureId(textureId), scale(scale), tileSize(tileSize) {}

void Map::loadMap(std::string filename, int mapSizeX, int mapSizeY) {
	std::fstream mapFile;
	mapFile.open(filename);

	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			char ch;
			mapFile.get(ch);
			int srcRectY = atoi(&ch) * tileSize;
			mapFile.get(ch);
			int srcRectX = atoi(&ch) * tileSize;
			addTile(srcRectX, srcRectY, x * (scale * tileSize), y * (scale * tileSize));
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::addTile(int srcX, int srcY, int x, int y) {
	Entity& newTile(entityManager.addEntity("Tile"));
	newTile.addComponent<TileComponent>(srcX, srcY, x, y, tileSize, scale, textureId);
}
