#pragma once
#include <SFML\Graphics.hpp>
const int  HEIGHT_MAP = 25;
const int  WIDTH_MAP = 40;
int map_i = 0;
int map_j = 0;
sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0         b 0                   0  b   0",
	"0    0      0   0000     0      0      0",
	"0 e  0   e  0    0       0      0      0",
	"0    00     0    0       0      0000   0",
	"0    0      0            0             0",
	"0           0 b          0             0",
	"00000     0000000000000000    0000000000",
	"0     e                          0b    0",
	"0                   0            0     0",
	"0  e      0         0                  0",
	"000000000000000000000000000000    000000",
	"0             0         b0             0",
	"0             0    0000000        0    0",
	"00000000      0    0   000        0    0",
	"0      0      0    0     0   000000    0",
	"0      0      0          0        0    0",
	"0      0      0      00000        0    0",
	"0000000000   00          0             0",
	"0                 00000                0",
	"000000000           0          0000    0",
	"0      b0           0             000000",
	"0       0000        000000    0        0",
	"0                             0        0",
	"0000000000000000000000000000000000000000",
};
