#include <iostream>
#include "Game.h"
#include "Vec2.h"
#include "EntityManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Map.h"

EntityManager entityManager;
AssetManager* Game::assetManager = new AssetManager(&entityManager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Map* map;

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

	loadLevel(0);

	running = true;
}

void Game::processInput() {
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

void Game::loadLevel(int levelNumber) {
	// Add assets to asset manager.
	assetManager->addTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->addTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->addTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	assetManager->addTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());

	map = new Map("jungle-tiletexture", 2, 32);
	map->loadMap("./assets/tilemaps/jungle.map", 25, 20);

	// Add components to entities and entities to entity manager.
	Entity& tankEntity(entityManager.addEntity("tank", ENEMY_LAYER));
	tankEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	tankEntity.addComponent<SpriteComponent>("tank-image");

	Entity& chopperEntity(entityManager.addEntity("chopper", PLAYER_LAYER));
	chopperEntity.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1, 10);
	chopperEntity.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	chopperEntity.addComponent<KeyboardControlComponent>("w", "s", "d", "a", "space");

	Entity& radarUI(entityManager.addEntity("radar-ui", UI_LAYER));
	radarUI.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarUI.addComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	entityManager.listEntities();
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

	entityManager.update(deltaTime);
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	if (!entityManager.hasEntities()) {
		return;
	}
	entityManager.render();

	SDL_RenderPresent(renderer);
}

void Game::destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

