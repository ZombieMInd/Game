#pragma once
//#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
//#include "Player.h"
//#include "Entity.h"

using namespace sf;
class Game{
private:
	//string state;
	int gameLevel;
	int levelOfComplexity;
	Clock clock;
	Image map_image;
	Texture map;
	Sprite s_map;
	Font font;
	Player *player;
public:
	Game();
	~Game();
	void init();
	void startGame();
};

