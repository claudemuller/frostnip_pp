#include <iostream>
#include "Game.h"

float projPosX = 0.0f;
float projPosY = 0.0f;
float projVelX = 0.5f;
float projVelY = 0.5f;

Game::Game() {
	running = false;
}

void Game::init(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_BORDERLESS
	);
	if (window == nullptr) {
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return;
	}

	running = true;
}

void Game::processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.key.type) {
		case SDL_QUIT: {
			running = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
			break;
		}
		default: {
			break;
		}
	}
}

void Game::update() {
	int waited_for = SDL_GetTicks();
	// Sleep the execution until the target time in milliseconds is reached.
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
	// Only call delay if processing is too fast in the current frame.
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
//	printf("FPS: %d\n", lastFrameTime - waited_for);
	float delta_time = (float)(SDL_GetTicks() - lastFrameTime) / 1000.0f;
	// Clamp deltaTime to a maximum value
//	delta_time = delta_time > 0.05f ? 0.05f : delta_time;
	// Sets the new ticks fo the current frame to be used in the next pass
	lastFrameTime = SDL_GetTicks();

	projPosX += projVelX;
	projPosY += projVelY;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_Rect projectile = {
			(int)projPosX,
			(int)projPosY,
			10,
			10
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &projectile);

	SDL_RenderPresent(renderer);
}

void Game::destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

