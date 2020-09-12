#include <iostream>
#include "Game.h"

int main() {
	Game* game = new Game();
	game->init(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->isRunning()) {
		game->processInput();
		game->update();
		game->render();
	}

	game->destroy();

	return 0;
}