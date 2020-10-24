#pragma once
#include <SFML/Graphics.hpp>
#include <random>
using namespace sf;

sf::View view;
void GetPlayerCoordinateForView(float x, float y) { 
	float tempX = x; float tempY = y;
	if (x < 540) tempX = 540;//убираем из вида левую сторону
	if (y < 500) tempY = 500;//верхнюю сторону
	if (y > 1850) tempY = 1820;//нижнюю сторону	
	if (x > 3250) tempX = 3250; // правую границу
	// я подобрал их такими чтобы они легли на карту
	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
}