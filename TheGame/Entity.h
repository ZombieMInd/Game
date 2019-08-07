#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "map.h"
#include "view.h"
#include <math.h>

const int BLOCK_SIZE = 90;
bool key = false;

const float PLAYER_SCALE = 0.8;
class Entity
{
	sf::Vector2f position;
	sf::Vector2i size;
	sf::Vector2f realSize;
	int height;
	int width;
	sf::String file;
	sf::Texture texture;
	sf::Vector2f posOld;
	float rotOld;
	bool attacking;
	float dir;//угол поворота
	float acceleration;//ускорение для более плавной физики 
public:
	sf::Vector2f speed;
	sf::Sprite sprite;
	Entity(sf::Vector2f pos, sf::Vector2f s, sf::String f);
	~Entity();
	void setTexturePos(sf::Vector2i pos, sf::Vector2i size);
	void setTextureForAnimation(sf::Vector2i pos, sf::Vector2i size);
	void textureRotate(sf::Vector2f pos);
	void move(float time);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	sf::Vector2f getRealSize();
	virtual void update(float time, sf::Vector2f pos) = 0;
	sf::Vector2f getPos();
	bool getAttacking();
	void setAttacking(bool isAttacking);
	sf::FloatRect getRect();
	virtual void getDamage(int damage) = 0;
	virtual int getHP() = 0;
	float getAngel(sf::Vector2f pos);
	sf::Vector2f getSpeed(sf::Vector2f pos);
	float distanceTo(sf::Vector2f pos);
	float getDir();
	void setOrigin(float x, float y);
};

std::list<Entity*> entities;
std::list<Entity*>::iterator iter;

Entity::Entity(sf::Vector2f pos, sf::Vector2f s, sf::String f)
{
	file = f;
	texture.loadFromFile("assets/" + file);
	sprite.setTexture(texture);
	position = pos;
	realSize = s;
	speed = sf::Vector2f(0, 0);
	posOld = sf::Vector2f(0, 0);
	rotOld = 0;
	sprite.setPosition(position.x, position.y);
	attacking = false;
}


Entity::~Entity()
{
}

void Entity::setTexturePos(sf::Vector2i pos, sf::Vector2i size) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
	sprite.scale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
	sprite.setOrigin(size.x / 2, size.y / 2);
}

void Entity::setTextureForAnimation(sf::Vector2i pos, sf::Vector2i size) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
}

void Entity::textureRotate(sf::Vector2f pos) {

	if (abs(pos.x - posOld.x) > 0.005 || abs(pos.y - posOld.y) > 0.005) {
		sprite.setRotation(0);
		float rotation = (getAngel(pos));
		sprite.rotate(rotation);
		dir = rotation;
	}
}


void Entity::move(float time) {
	position.x += speed.x * time;
	position.y += speed.y * time;
	sprite.setPosition(position.x, position.y);
}

void Entity::setPosition(sf::Vector2f pos) {
	position = pos;
	sprite.setPosition(pos);
}

void Entity::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

sf::Vector2f Entity::getRealSize() {
	return realSize;
}

sf::Vector2f Entity::getPos() {
	return position;
}

bool Entity::getAttacking() {
	return attacking;
}

void Entity::setAttacking(bool isAttacking) {
	attacking = isAttacking;
}

sf::FloatRect Entity::getRect() {
	return sf::FloatRect(position.x - realSize.x / 2, position.y - realSize.y / 2,
		realSize.x, realSize.y);
}

float Entity::getAngel(sf::Vector2f pos) {
	sf::Vector2f dir;
	dir.x = pos.x - position.x;
	dir.y = pos.y - position.y;
	return (atan2(dir.y, dir.x) * 180. / 3.14159265);
}

sf::Vector2f Entity::getSpeed(sf::Vector2f pos) {
	sf::Vector2f dir;
	dir.x = pos.x - position.x;
	dir.y = pos.y - position.y;
	float hyp = sqrt(dir.x*dir.x + dir.y*dir.y);
	sf::Vector2f res;
	res.x = dir.x / hyp;
	res.y = dir.y / hyp;
	return res;
}

float Entity::distanceTo(sf::Vector2f pos) {
	sf::Vector2f dir;
	dir.x = pos.x - position.x;
	dir.y = pos.y - position.y;
	return sqrtf(dir.x * dir.x + dir.y * dir.y);
}

float Entity::getDir() {
	return dir;
}

void Entity::setOrigin(float x, float y) {
	sprite.setOrigin(x, y);
}

//PLAYER CLASS=======================================================

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

void Player::controle() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		speed.y = -0.3;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
		speed.y = 0.3;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		speed.x = -0.3;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
		speed.x = 0.3;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		float timePassed = attackTimer.getElapsedTime().asMilliseconds();
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
		//int j = dx <= 0 ? x / BLOCK_SIZE : (startX + 2 * w) / BLOCK_SIZE;
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
		//int i = dy <= 0 ? y / BLOCK_SIZE : (startY + 2 * h) / BLOCK_SIZE;
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
	//std::cout << attackTimer.getElapsedTime().asMilliseconds() << std::endl;
	
}

//ENEMY CLASS==========================================
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
	enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x*time, speed.y*time);
	textureRotate(playerPos);
	sprite.setColor(sf::Color(255, 255, 255, 255));
}

void Enemy::behavior(sf::Vector2f playerPos) {
	float time = behaviorTimer.getElapsedTime().asMilliseconds();
	if (distanceTo(playerPos) <= 700 && distanceTo(playerPos) > 400) {
		if (time > 100) {
			speed = getSpeed(playerPos);
			//enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
			/*std::cout << "distance " << distanceTo(playerPos) << std::endl;
			std::cout << "speed " << speed.x << "  " << speed.y << std::endl;*/
			behaviorTimer.restart();
		}
	}
	else if (distanceTo(playerPos) <= 400 && distanceTo(playerPos) > 120) {
		//float time = behaviorTimer.restart().asMilliseconds();
		speed = getSpeed(playerPos);
		//enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
			/*std::cout << "distance2222 " << distanceTo(playerPos) << std::endl;
			std::cout << "time 2222" << time << std::endl;
			std::cout << "speed " << speed.x << "  " << speed.y << std::endl;*/
		//behaviorTimer.restart();
	}
	else if (distanceTo(playerPos) <= 120) {	
		//std::cout << "LASTD " << distanceTo(playerPos)  << std::endl;
		speed.x = 0;
		speed.y = 0;
	}
}

void Enemy::enemyInteractionWithMap(float x, float y, float dx, float dy) {
	float h, w;
	bool chcoords = true;
	h = getRealSize().y / 2;
	w = getRealSize().x / 2;
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
				chcoords = false;
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
		//setPosition(x, y);
	}
	if (dy != 0) {
		int i = dy <= 0 ? y / BLOCK_SIZE : (startY + 2 * h) / BLOCK_SIZE;
		for (int j = x / BLOCK_SIZE; j < (startX + 2 * w) / BLOCK_SIZE; j++) {
			if (TileMap[i][j] == '0') {
				chcoords = false;
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
		//setPosition(x, y);
	}
	if (chcoords==false){
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