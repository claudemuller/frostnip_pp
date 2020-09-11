#include <iostream>
#include "Game.h"
#include "Vec2.h"
#include "EntityManager.h"

EntityManager entityManager;
SDL_Renderer* Game::renderer;

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

void loadLevel(int levelNumber) {
	Entity block = entityManager.addEntity("test");
//	block.addComponent<TransformComponent>();
}

void Game::update() {
	int waited_for = SDL_GetTicks();
	// Sleep the execution until the target time in milliseconds is reached.
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
	// Only call delay if processing is too fast in the current frame.
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}
//	printf("FPS: %d\n", lastFrameTime - waited_for);
	float deltaTime = (float)(SDL_GetTicks() - lastFrameTime) / 1000.0f;
	// Clamp deltaTime to a maximum value
	deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;
	// Sets the new ticks fo the current frame to be used in the next pass
	lastFrameTime = SDL_GetTicks();
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

