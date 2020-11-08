#pragma once
#include "Entity.h"
#include "Player.h"
#include <string>

class Enemy : public Entity {
private:
	int hp;
	sf::Clock attackTimer;
	sf::Clock  behaviorTimer;
	String enemyType;
	sf::Vector2f radiusAttack;// первое это длина прямоугольника который BadDog кусает, вторая это ширина
	Player *player;
	sf::Clock changeSpriteTimer;
public:
	Enemy(sf::Vector2f pos, int health, String type);
	void update(float time, sf::Vector2f pos);
	void runAnimation();
	void behavior(sf::Vector2f playerPos);
	void enemyInteractionWithMap(float x, float y, float dx, float dy);
	void makeDamage(int damage);
	void setPlayer(Player *player);
	int setEnemyAttack();
	int getHP();
	void moveAnimation();
};

Enemy::Enemy(sf::Vector2f pos, int health, String type) :
	Entity(pos, sf::Vector2f(154, 59), "G_v06.png") {
	hp = health;
	enemyType = "BadDog";
	setTexturePos(sf::Vector2i(10, 440), sf::Vector2i(154, 59));
}

void Enemy::setPlayer(Player *player) {
	this->player = player;
}

void Enemy::update(float time, sf::Vector2f playerPos) {

	if (changeSpriteTimer.getElapsedTime().asMilliseconds() > 100 && hp < 100) {
		sprite.setColor(sf::Color::White);
	}

	behavior(playerPos);
	if (speed.x != 0 || speed.y != 0) {
		runAnimation();
		if (behaviorTimer.getElapsedTime().asMilliseconds() > 250) {
			behaviorTimer.restart();
		}
	}
	move(time);
	enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x*time, speed.y*time);
	textureRotate(playerPos);
	//sprite.setColor(sf::Color(255, 255, 255, 255));
	float damage = setEnemyAttack();
	if (getAttacking()) {
		if ((distanceTo(sprite.getPosition()) <= radiusAttack.x)) {
			if (attackTimer.getElapsedTime().asMilliseconds() > 300) {
				player->makeDamage(damage * 10);
				std::cout << "Damage to player " << damage * 10 << "; player hp " << player->getHP() << std::endl;
				attackTimer.restart();
			}
		}
		setAttacking(false);
	}
}


void Enemy::behavior(sf::Vector2f playerPos) {
	float time = behaviorTimer.getElapsedTime().asMilliseconds();
	//std::cout << "Distance To PLayer " << distanceTo(playerPos) << std::endl;
	if (distanceTo(playerPos) <= 700 && distanceTo(playerPos) > 400) {
		if (time > 100) {
			speed = getSpeed(playerPos);
			behaviorTimer.restart();
		}
	}
	else if (distanceTo(playerPos) <= 400 && distanceTo(playerPos) > 120) {
		speed.x = getSpeed(playerPos).x / 10;
		speed.y = getSpeed(playerPos).y / 10;
	}
	else if (distanceTo(playerPos) <= 120) {
		speed.x = 0;
		speed.y = 0;
		setAttacking(true);
		attackTimer.getElapsedTime().asMilliseconds();
	}
}

void Enemy::enemyInteractionWithMap(float x, float y, float dx, float dy) {
	float h, w;
	h = getRealSize().y / 2;
	w = getRealSize().x / 2;
	y -= h;
	x -= w;
	float startX = x;
	float startY = y;
	float newX;
	float oldX = x - dx;
	float oldY = y - dy;
	int j = dx <= 0 ? x / BLOCK_SIZE : (startX + 2 * w) / BLOCK_SIZE;
	if (dx != 0) {
		for (int i = y / BLOCK_SIZE; i < (startY + 2 * h) / BLOCK_SIZE; i++) {
			if (TileMap[i][j] == '0') {
				if (dx > 0 && TileMap[i][j - 1] != '0' && oldX <= j * BLOCK_SIZE - 2 * w) {
					x = j * BLOCK_SIZE - 2 * w;
					break;
				}
				if (dx < 0 && TileMap[i][j + 1] != '0' && oldX >= (j + 1) * BLOCK_SIZE) {
					x = (j + 1) * BLOCK_SIZE;
					break;
				}
			}
		}
		setPosition(x + w, y + h);
	}
	int i = dy <= 0 ? y / BLOCK_SIZE : (startY + 2 * h) / BLOCK_SIZE;
	if (dy != 0) {
		for (int j = x / BLOCK_SIZE; j < (startX + 2 * w) / BLOCK_SIZE; j++) {
			if (TileMap[i][j] == '0') {
				if (dy > 0 && TileMap[i - 1][j] != '0' && oldY <= i * BLOCK_SIZE - 2 * h) {
					y = i * BLOCK_SIZE - 2 * h;
					break;
				}
				if (dy < 0 && TileMap[i + 1][j] != '0' && oldY >= (i + 1) * BLOCK_SIZE) {
					y = (i + 1) * BLOCK_SIZE;
					break;
				}
			}
		}
		setPosition(x + w, y + h);
	}
	speed.x = 0;
	speed.y = 0;
}

void Enemy::makeDamage(int damage) {
	changeSpriteTimer.restart();
	hp -= damage;
	sprite.setColor(sf::Color(255, 0, 0, 100));
	std::cout << "Damage to enemy " << damage << " Enemy hp " << hp << std::endl;
}

int Enemy::getHP() {
	return hp;
}


void Enemy::moveAnimation() {

}

//определение атаки в зависимости от Enemy; будет умножаться на 10+;ну и радиус поражения в зависимости
// от Enemy  тоже разный
int Enemy::setEnemyAttack() {
	int realDam = 0;
	if (enemyType == "BadDog") {
		realDam = 1;
		radiusAttack = sf::Vector2f(80, 5);
	}
	return realDam;
}
void Enemy::runAnimation() {
	if (behaviorTimer.getElapsedTime().asMilliseconds() < 20) {
		setTextureForAnimation(sf::Vector2i(200, 440), sf::Vector2i(154, 59));
	}
	if (behaviorTimer.getElapsedTime().asMilliseconds() > 100 &&
		behaviorTimer.getElapsedTime().asMilliseconds() < 200) {
		setTextureForAnimation(sf::Vector2i(370, 440), sf::Vector2i(154, 59));
	}
	if (behaviorTimer.getElapsedTime().asMilliseconds() > 200 &&
		behaviorTimer.getElapsedTime().asMilliseconds() < 400) {
		setTextureForAnimation(sf::Vector2i(560, 440), sf::Vector2i(154, 59));
	}
	if (behaviorTimer.getElapsedTime().asMilliseconds() > 400 &&
		behaviorTimer.getElapsedTime().asMilliseconds() < 500) {
		setTextureForAnimation(sf::Vector2i(10, 440), sf::Vector2i(154, 59));
	}

}