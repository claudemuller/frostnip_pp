#include <iostream>
#include "Constants.h"
#include "Game.h"

int main() {
	Game *game = new Game();
	game->init(SCREEN_WIDTH, SCREEN_HEIGHT);

	while (game->isRunning()) {
		game->processInput();
		game->update();
		game->render();
	}

	game->destroy();

	return 0;
}