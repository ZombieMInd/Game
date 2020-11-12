#pragma once
#include "Game.h"
using namespace sf;

int main(){

	Game game;
	while (game.isPlaying()) {
		game.init();
		if (game.play()) {
			game.restartGame();
		}
	}
	
	return EXIT_SUCCESS;
}