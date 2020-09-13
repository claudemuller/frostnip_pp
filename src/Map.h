#ifndef FROSTBYTE_MAP_H
#define FROSTBYTE_MAP_H

#include <string>

class Map {
public:
	Map(std::string textureId, int scale, int tileSize);

	void loadMap(std::string filename, int width, int height);
	void addTile(int srcX, int srcY, int x, int y);

private:
	std::string textureId;
	int scale;
	int tileSize;
};

#endif //FROSTBYTE_MAP_H
