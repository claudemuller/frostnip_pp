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

