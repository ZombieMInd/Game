#pragma once
#include "Entity.h"

class Player : public Entity {
private:
	int hp;
	sf::Vector2f attackCircle;//первая координата - r радиус поражения, вторая fi - угол поражения
	sf::String weapon;
	sf::Clock attackTimer; //таймер засекающий время между ударами
	int attackSpeed; //кол-во милсек до следующего удара
	int animationFrame;

public:
	Player(sf::Vector2f pos, int health);
	Player();
	void controle();
	void update(float time, sf::Vector2f pos);
	void interactionWithMap(float x, float y, float dx, float dy);
	void opening_chest();
	void setAttackCircle();
	void getDamage(int damage);
	int getHP();
	void attackAnimation();
	
};

Player::Player(sf::Vector2f pos, int health) :
	Entity(pos, sf::Vector2f(45, 45), "PersNew.png") {
	hp = health;
	setTexturePos(sf::Vector2i(0, 0), sf::Vector2i(137, 254));
	setOrigin(25, 132);
	attackSpeed = 600;
	attackCircle = sf::Vector2f(0, 0);
	animationFrame = 0;
}

Player::Player()
{
}

void Player::controle() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		speed.y = -0.3f;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
		speed.y = 0.3f;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		speed.x = -0.3f;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
		speed.x = 0.3f;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		int timePassed = attackTimer.getElapsedTime().asMilliseconds();
		if (timePassed >= attackSpeed) {
			setAttacking(true);
			attackTimer.restart();
			//
			std::cout << getAngel(sf::Vector2f(1000, 1000)) << " " << distanceTo(sf::Vector2f(1000, 1000)) << std::endl;
		}
	}
}

void Player::update(float time, sf::Vector2f pos) {
	GetPlayerCoordinateForView(sprite.getPosition().x, sprite.getPosition().y);
	controle();
	attackAnimation();
	move(time);
	interactionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x*time, speed.y*time);
	textureRotate(pos);
	setAttackCircle();
	if (getAttacking()) {
		for (auto ent : entities) {
			if (distanceTo(ent->getPos()) <= attackCircle.x &&
				getAngel(ent->getPos()) < getDir() + attackCircle.y &&
				getAngel(ent->getPos()) > getDir() - attackCircle.y)
				//std::cout << getRect().left << " " << getRect().top << " " << 
				//getRect().height << " " << getRect().width << std::endl;
				ent->getDamage(10);
		}
		setAttacking(false);
	}
}

void Player::interactionWithMap(float x, float y, float dx, float dy) {
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
	if (TileMap[i][j] == 'b') {
		key = true;
		map_i = i;
		map_j = j;
	}
	speed.x = 0;
	speed.y = 0;
}

void Player::opening_chest() {
	TileMap[map_i][map_j] = 't';
	weapon = "sword";
	sprite.setTextureRect(sf::IntRect(0, 365, 90, 455));
}

void Player::setAttackCircle() {
	if (weapon == "sword")
		attackCircle = sf::Vector2f(150, 60);
}

void Player::getDamage(int damage) {
	hp -= damage;
	sprite.setColor(sf::Color(255, 0, 0, 100));
}

int Player::getHP() {
	return hp;
}

void Player::attackAnimation() {
	if (attackTimer.getElapsedTime().asMilliseconds() < 10) {
		animationFrame = 1;
		setTextureForAnimation(sf::Vector2i(145 * animationFrame, 0), sf::Vector2i(137, 254));
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 50 &&
		attackTimer.getElapsedTime().asMilliseconds() < 100) {
		animationFrame = 2;
		setTextureForAnimation(sf::Vector2i(145 * animationFrame, 0), sf::Vector2i(137, 254));
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 100 &&
		attackTimer.getElapsedTime().asMilliseconds() < 200) {
		animationFrame = 3;
		setTextureForAnimation(sf::Vector2i(145 * animationFrame, 0), sf::Vector2i(137, 254));
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 200 &&
		attackTimer.getElapsedTime().asMilliseconds() < 250) {
		animationFrame = 4;
		setTextureForAnimation(sf::Vector2i(145 * animationFrame, 0), sf::Vector2i(137, 254));
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 250) {
		animationFrame = 0;
		setTextureForAnimation(sf::Vector2i(145 * animationFrame, 0), sf::Vector2i(137, 254));
	}
}