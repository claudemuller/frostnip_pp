#ifndef FROSTNIP_PP_MAP_H
#define FROSTNIP_PP_MAP_H

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

#endif //FROSTNIP_PP_MAP_H
