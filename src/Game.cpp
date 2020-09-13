#include <iostream>
#include "Game.h"
#include "Vec2.h"
#include "EntityManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Map.h"
#include "Components/TextLabelComponent.h"

EntityManager entityManager;
AssetManager* Game::assetManager = new AssetManager(&entityManager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;
bool Game::debug = false;

Game::Game() {
	running = false;
}

void Game::init(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
		return;
	}

	if (TTF_Init() != 0) {
		std::cerr << "Failed to init TTF: " << TTF_GetError() << std::endl;
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
	bool keyDown;
	switch (event.key.type) {
		case SDL_QUIT: {
			running = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (keyDown) {
				break;
			}
			keyDown = true;
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
			if (event.key.keysym.sym == SDLK_F1) {
				debug = !debug;
			}
			break;
		}
		case SDL_KEYUP: {
			keyDown = false;
			break;
		}
		default: {
			break;
		}
	}
}

Entity& player(entityManager.addEntity("chopper", PLAYER_LAYER));
void Game::loadLevel(int levelNumber) {
	// Add assets to asset manager.
	assetManager->addTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->addTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->addTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	assetManager->addTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
	assetManager->addTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
	assetManager->addFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

	map = new Map("jungle-tiletexture", 2, 32);
	map->loadMap("./assets/tilemaps/jungle.map", 25, 20);

	// Add components to entities and entities to entity manager.
	Entity& tankEntity(entityManager.addEntity("tank", ENEMY_LAYER));
	tankEntity.addComponent<TransformComponent>(106, 495, 20, 0, 32, 32, 1);
	tankEntity.addComponent<SpriteComponent>("tank-image");
	TransformComponent* tankTransform = tankEntity.getComponent<TransformComponent>();
	tankEntity.addComponent<ColliderComponent>(
			"ENEMY",
			tankTransform->position.getX(),
			tankTransform->position.getY(),
			tankTransform->width,
			tankTransform->height
	);

	player.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1, 10);
	player.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.addComponent<KeyboardControlComponent>("w", "s", "d", "a", "space");
	TransformComponent* playerTransform = player.getComponent<TransformComponent>();
	player.addComponent<ColliderComponent>(
			"PLAYER",
			playerTransform->position.getX(),
			playerTransform->position.getY(),
			playerTransform->width,
			playerTransform->height
	);

	Entity& heliport(entityManager.addEntity("heliport", UI_LAYER));
	struct heliportDims {
		int x;
		int y;
		int w;
		int h;
	} heliportDims{470, 420, 32, 32};
	heliport.addComponent<TransformComponent>(heliportDims.x, heliportDims.y, 0, 0, heliportDims.w, heliportDims.h, 1);
	heliport.addComponent<SpriteComponent>("heliport-image");
	heliport.addComponent<ColliderComponent>("LEVEL_COMPLETE", heliportDims.x, heliportDims.y, heliportDims.w, heliportDims.h);

	Entity& radarUI(entityManager.addEntity("radar-ui", UI_LAYER));
	radarUI.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarUI.addComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	Entity& lblLevelName(entityManager.addEntity("ui-level-name", UI_LAYER));
	lblLevelName.addComponent<TextLabelComponent>(10, 10, "First Level...", "charriot-font", WHITE);

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
	checkCollisions();
	handleCameraMovement();
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

void Game::handleCameraMovement() {
	TransformComponent* playerTransform = player.getComponent<TransformComponent>();

	camera.x = playerTransform->position.getX() - (WINDOW_WIDTH / 2);
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.x = camera.x > WINDOW_WIDTH ? WINDOW_WIDTH : camera.x;

	camera.y = playerTransform->position.getY() - (WINDOW_WIDTH / 2);
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.y = camera.y > WINDOW_HEIGHT ? WINDOW_HEIGHT : camera.y;
}

void Game::checkCollisions() {
	CollisionType collisionType = entityManager.checkCollisions();
	if (collisionType == PLAYER_ENEMY_COLLISION) {
		processGameOver();
	} else if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
		processNextLevel(1);
	}
}

void Game::processGameOver() {
	std::cout << "Game over." << std::endl;
	running = false;
}

void Game::processNextLevel(int level) {
	std::cout << "Next level." << std::endl;
	running = false;
}

void Game::destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}
