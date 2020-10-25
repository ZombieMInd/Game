#pragma once
#include <iostream>
//#include "Player.h"
using namespace std;
class Game{
private:
	string state;
	int lvl;
	//Player player;
public:
	Game();
	~Game();
	void init();
	void startGame();
};

