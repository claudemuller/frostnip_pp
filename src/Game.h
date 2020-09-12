#ifndef FROSTNIP_PP_GAME_H
#define FROSTNIP_PP_GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Constants.h"
#include "EntityManager.h"
#include "Entity.h"

class AssetManager;

class Game {
public:
	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Event event;

	Game();

	void init(int width, int height);
	void processInput();
	void loadLevel(int levelNumber);
	void update();
	void render();
	void destroy();
	bool isRunning() const { return running; };

private:
	SDL_Window* window;
	bool running;
	int lastFrameTime = 0;
};

#endif //FROSTNIP_PP_GAME_H
