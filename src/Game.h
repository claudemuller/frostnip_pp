#ifndef FROSTNIP_PP_GAME_H
#define FROSTNIP_PP_GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Constants.h"

class Game {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Game();

	bool isRunning() const { return running; };
	void init(int width, int height);
	void processInput();
	void update();
	void render();
	void destroy();

private:
	bool running;
	int lastFrameTime = 0;
};

#endif //FROSTNIP_PP_GAME_H
