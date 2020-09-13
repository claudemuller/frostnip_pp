#ifndef FROSTNIP_PP_GAME_H
#define FROSTNIP_PP_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Constants.h"
#include "EntityManager.h"
#include "Entity.h"

class AssetManager;

class Game {
public:
	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Event event;
	static SDL_Rect camera;
	static bool debug;

	Game();

	void init(int width, int height);
	void processInput();
	void loadLevel(int levelNumber);
	void update();
	void render();
	void handleCameraMovement();
	void checkCollisions();
	void destroy();
	bool isRunning() const { return running; };
	void processGameOver();
	void processNextLevel(int level);

private:
	SDL_Window* window;
	bool running;
	int lastFrameTime = 0;
	float currentFPS = 0.0;
};

#endif //FROSTNIP_PP_GAME_H
