#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
private:
	int hp;
	sf::Clock attackTimer;
	sf::Clock  behaviorTimer;
public:
	Enemy(sf::Vector2f pos, int health);
	void update(float time, sf::Vector2f pos);
	void behavior(sf::Vector2f playerPos);
	void enemyInteractionWithMap(float x, float y, float dx, float dy);
	void getDamage(int damage);
	int getHP();
};

Enemy::Enemy(sf::Vector2f pos, int health) :
	Entity(pos, sf::Vector2f(154, 59), "G_v05.png") {
	hp = health;
	setTexturePos(sf::Vector2i(260, 265), sf::Vector2i(154, 59));
	void enemyInteractionWithMap(float x, float y, float dx, float dy);
	void update(float time, sf::Vector2f pos);
}

void Enemy::update(float time, sf::Vector2f playerPos) {
	behavior(playerPos);
	move(5);
	//enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x*5, speed.y*5);
	textureRotate(playerPos);
	sprite.setColor(sf::Color(255, 255, 255, 255));
}

inline void Enemy::behavior(sf::Vector2f playerPos)
{
	float time = behaviorTimer.getElapsedTime().asMilliseconds();

	if (distanceTo(playerPos) <= 500 && time > 100) {
		speed.x = cos((int)getAngel(playerPos)) / 100;
		speed.y = sin((int)getAngel(playerPos)) / 100;
		behaviorTimer.restart();
	}
	if (distanceTo(playerPos) <= 200) {
		float time = behaviorTimer.restart().asMilliseconds();
		if (time > 2500) {
			speed.x *= 4;
			speed.y *= 4;

		}
		if (distanceTo(playerPos) <= 700 && distanceTo(playerPos) > 400) {
			if (time > 100) {
				speed = getSpeed(playerPos);
				enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
				behaviorTimer.restart();
			}
		}
		else if (distanceTo(playerPos) <= 400 && distanceTo(playerPos) > 120) {
			speed = getSpeed(playerPos);
			enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
		}
		else if (distanceTo(playerPos) <= 120) {
			speed.x = 0;
			speed.y = 0;
		}
	}



	if (distanceTo(playerPos) <= 200) {
		float time = behaviorTimer.restart().asMilliseconds();
		if (time > 2500) {
			speed.x *= 4;
			speed.y *= 4;

		}
		if (distanceTo(playerPos) <= 700 && distanceTo(playerPos) > 400) {
			if (time > 100) {
				speed = getSpeed(playerPos);
				enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
				behaviorTimer.restart();
			}
		}
		else if (distanceTo(playerPos) <= 400 && distanceTo(playerPos) > 120) {
			speed = getSpeed(playerPos);
			enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
		}
		else if (distanceTo(playerPos) <= 120) {
			speed.x = 0;
			speed.y = 0;
		}
	}
}

	void Enemy::enemyInteractionWithMap(float x, float y, float dx, float dy) {
		float h, w;
		bool chcoords = true;
		w = getRealSize().y / 2;
		h = getRealSize().x / 2;
		y -= h;
		x -= w;
		float startX = x;
		float startY = y;
		float newX;
		float oldX = x - dx;
		float oldY = y - dy;
		if (dx != 0) {
			int j = dx <= 0 ? x / BLOCK_SIZE : (startX + 2 * w) / BLOCK_SIZE;
			for (int i = y / BLOCK_SIZE; i < (startY + 2 * h) / BLOCK_SIZE; i++) {
				if (TileMap[i][j] == '0') {
					if (dx > 0 && TileMap[i][j - 1] != '0' && oldX <= j * BLOCK_SIZE - 2 * w) {
						x = j * BLOCK_SIZE - 2 * w;
						chcoords = false;
						setPosition(x + w, y + h);
						break;
					}
					if (dx < 0 && TileMap[i][j + 1] != '0' && oldX >= (j + 1) * BLOCK_SIZE) {
						x = (j + 1) * BLOCK_SIZE;
						chcoords = false;
						setPosition(x + w, y + h);
						break;
					}
				}
			}
		}
		if (dy != 0) {
			int i = dy <= 0 ? y / BLOCK_SIZE : (startY + 2 * h) / BLOCK_SIZE;
			for (int j = x / BLOCK_SIZE; j < (startX + 2 * w) / BLOCK_SIZE; j++) {
				if (TileMap[i][j] == '0') {
					if (dy > 0 && TileMap[i - 1][j] != '0' && oldY <= i * BLOCK_SIZE - 2 * h) {
						y = i * BLOCK_SIZE - 2 * h;
						chcoords = false;
						setPosition(x + w, y + h);
						break;
					}
					if (dy < 0 && TileMap[i + 1][j] != '0' && oldY >= (i + 1) * BLOCK_SIZE) {
						y = (i + 1) * BLOCK_SIZE;
						chcoords = false;
						setPosition(x + w, y + h);
						break;
					}
				}
			}
		}
		if (!chcoords) {
			speed.x = 0;
			speed.y = 0;
		}
	}

	void Enemy::getDamage(int damage) {
		hp -= damage;
		sprite.setColor(sf::Color(255, 0, 0, 100));
		std::cout << damage << std::endl;
	}

	int Enemy::getHP() {
		return hp;
	}