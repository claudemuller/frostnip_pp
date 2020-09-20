#include <iostream>
#include <string>
#include "Utils/Benchmark.h"
#include "Game.h"
#include "Map.h"
#include "Components/SpriteComponent.h"
#include "Components/TextLabelComponent.h"

EntityManager entityManager;
AssetManager* Game::assetManager = new AssetManager(&entityManager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Camera Game::camera = {};
Map* map;
bool Game::debug;

Game::Game() {
	running = false;
	debug = false;
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

	loadLevel(1);

	// TODO: If debug?
	Benchmark::start();

	CollisionEngine::init();

	running = true;
}

void Game::processInput() {
	SDL_PollEvent(&event);

//	SDL_Joystick *joystick;
//	SDL_JoystickEventState(SDL_ENABLE);
//	joystick = SDL_JoystickOpen(0);

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
//		case SDL_JOYAXISMOTION: {  /* Handle Joystick Motion */
//			if ((event.jaxis.value < -3200) || (event.jaxis.value > 3200)) {
//				/* code goes here */
//			}
//			break;
//		}
//		case SDL_JOYBUTTONDOWN: { /* Handle Joystick Button Presses */
//			std::cout << "but " << event.jbutton.button << std::endl;
//			if (event.jbutton.button == 0) {
//				/* code goes here */
//			}
//			break;
//		}
		default: {
			break;
		}
	}
}

void Game::loadLevel(int levelNumber) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	std::string levelName = "Level" + std::to_string(levelNumber);
	lua.script_file("./assets/scripts/" + levelName + ".lua");
	// TODO: Check if file was correct.

	sol::table levelData = lua[levelName];

	// Load assets from lua file.
	sol::table levelAssets = levelData["assets"];
	// TODO: sanitise.
	unsigned int assetIndex = 0;
	while (true) {
		sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
		if (existsAssetIndexNode == sol::nullopt) {
			break;
		} else {
			sol::table asset = levelAssets[assetIndex];
			std::string assetType = asset["type"];
			if (assetType == "texture") {
				std::string assetId = asset["id"];
				std::string assetFile = asset["file"];
				assetManager->addTexture(assetId, assetFile.c_str());
			}

			if (assetType == "font") {
				std::string assetId = asset["id"];
				std::string assetFile = asset["file"];
				int fontSize = static_cast<int>(asset["fontSize"]);
				assetManager->addFont(assetId, assetFile.c_str(), fontSize);
			}
		}
		assetIndex++;
	}

	// Load map from lua file.
	sol::table levelMap = levelData["map"];
	std::string mapTextureId = levelMap["textureAssetId"];
	std::string mapFile = levelMap["file"];
	map = new Map(
			mapTextureId,
			// TODO: sanitise value.
			static_cast<int>(levelMap["scale"]),
			static_cast<int>(levelMap["tileSize"])
	);
	map->loadMap(
			mapFile,
			static_cast<int>(levelMap["mapSizeX"]),
			static_cast<int>(levelMap["mapSizeY"])
	);

	// Load entities from lua file.
	sol::table levelEntities = levelData["entities"];
	// TODO: sanitise.
	unsigned int entityIndex = 0;
	while (true) {
		sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
		if (existsEntityIndexNode == sol::nullopt) {
			break;
		} else {
			// TODO: sanitise.
			sol::table scriptEntity = levelEntities[entityIndex];
			std::string entityName = scriptEntity["name"];
			LayerType entityLayer = scriptEntity["layer"];
			sol::table entityComponents = scriptEntity["components"];

			Entity& entity(entityManager.addEntity(entityName, entityLayer));
			entity.addComponentsFromTable(entityComponents);
		}
		entityIndex++;
	}
}

void Game::update() {
	// Sleep the execution until the target time in milliseconds is reached.
	int timeToWait = FRAME_TARGET_TIME - SDL_GetTicks() - lastFrameTime;
	// Only call delay if processing is too fast in the current frame.
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}
	currentFPS = (float)(SDL_GetTicks() - lastFrameTime);

	// TODO: rather control this with a DEBUG_LAYER.
	if (Game::debug) {
//		Entity* lblFPS = entityManager.getEntity("ui-level-name");
//		if (lblFPS != NULL) {
//			TextLabelComponent* lblFPSText = lblFPS->getComponent<TextLabelComponent>();
//			lblFPSText->setLabelText(std::to_string(currentFPS), "charriot-font");
//		}
	}

	float deltaTime = currentFPS / 1000.0f;
	// Clamp deltaTime to a maximum value
	deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;
	// Sets the new ticks fo the current frame to be used in the next pass
	lastFrameTime = SDL_GetTicks();

	entityManager.update(deltaTime);

	checkCollisions();
	Benchmark::log();

	CollisionEngine::update();

	camera.update(deltaTime);
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	if (!entityManager.hasEntities()) {
		return;
	}
	entityManager.render();

	CollisionEngine::render();

	SDL_RenderPresent(renderer);
}

void Game::checkCollisions() {
	// Old collision.
//	CollisionType collisionType = entityManager.checkCollisions();
//	if (collisionType == PLAYER_ENEMY_COLLISION || collisionType == PLAYER_PROJECTILE_COLLISION) {
//		processGameOver();
//	} else if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
//		processNextLevel(1);
//	}

	CollisionEngine::update();
	CollisionType collisionType = CollisionEngine::checkCollisions();
	if (collisionType == PLAYER_ENEMY_COLLISION || collisionType == PLAYER_PROJECTILE_COLLISION) {
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
	Benchmark::stop();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}
