#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "map.h"
#include "view.h"

const int BLOCK_SIZE = 90;
bool key = false;

const float PLAYER_SCALE = 0.5;
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
	sf::Vector2f direction;
	float rotOld;

public:
	sf::Vector2f speed;
	sf::Sprite sprite;
	Entity(sf::Vector2f pos, sf::Vector2i s, sf::String f);
	~Entity();
	void setTexturePos(sf::Vector2i pos);
	void textureRotate(sf::Vector2f pos);
	void move(float time);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	sf::Vector2f getRealSize();
	virtual void update(float time, sf::Vector2f pos) = 0;
};

std::list<Entity*> entities;
std::list<Entity*>::iterator iter;

Entity::Entity(sf::Vector2f pos, sf::Vector2i s, sf::String f)
{
	file = f;
	texture.loadFromFile("assets/" + file);
	sprite.setTexture(texture);
	position = pos;
	size = s;
	speed = sf::Vector2f(0, 0);
	posOld = sf::Vector2f(0, 0);
	direction = sf::Vector2f(0, 1);
	rotOld = 0;
	sprite.setPosition(position.x, position.y);
}


Entity::~Entity()
{
}

void Entity::setTexturePos(sf::Vector2i pos) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
	sprite.scale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
	realSize.x = size.x*PLAYER_SCALE;
	realSize.y = size.y*PLAYER_SCALE;
	sprite.setOrigin(size.x / 2, size.y / 2);
}

void Entity::textureRotate(sf::Vector2f pos) {
	sf::Vector2f dir;
	if (abs(pos.x - posOld.x) > 0.005 || abs(pos.y - posOld.y) > 0.005) {
		sprite.setRotation(0);
		dir.x = pos.x - position.x;
		dir.y = pos.y - position.y;
		float rotation = (atan2(dir.y, dir.x) * 180. / 3.14159265);
		//std::cout << rotation << " " <<  std::endl;
		sprite.rotate(rotation);
	}
}


void Entity::move(float time) {
	position.x += speed.x * time;
	position.y += speed.y * time;
	//std::cout << time << std::endl;
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


class Player : public Entity {
private:
	int hp;

public:
	Player(sf::Vector2f pos, int health);
	void controle();
	void update(float time, sf::Vector2f pos);
	void interactionWithMap(float x, float y, float dx, float dy);
	void opening_chest();
};

Player::Player(sf::Vector2f pos, int health) :
	Entity(pos, sf::Vector2i(90, 90), "G_v01.png") {
	hp = health;
	setTexturePos(sf::Vector2i(235, 100));

}

void Player::controle() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		speed.y = -0.3;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
		speed.y = 0.3;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		speed.x = -0.3;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
		speed.x = 0.3;
	}
}

void Player::update(float time, sf::Vector2f pos) {
	GetPlayerCoordinateForView(sprite.getPosition().x, sprite.getPosition().y);
	controle();
	move(time);
	interactionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
	textureRotate(pos);
}

void Player::interactionWithMap(float x, float y, float dx, float dy) {
	float h, w;
	h = getRealSize().y / 2;
	w = getRealSize().x / 2;
	y -= h;
	x -= w;
	float startX = x;
	float startY = y;
	for (int i = y / BLOCK_SIZE; i < (startY + 2 * h) / BLOCK_SIZE; i++) {
		for (int j = x / BLOCK_SIZE; j < (startX + 2 * w) / BLOCK_SIZE; j++) {
			//int j = (startX + w) / blcsize;
			if (TileMap[i][j] == '0') {
				if (dy > 0) {
					y = i * BLOCK_SIZE - 2 * h;
				}
				if (dy < 0) {
					y = (i + 1) * BLOCK_SIZE;
				}
				if (dx > 0) {
					x = j * BLOCK_SIZE - 2 * w;
				}
				if (dx < 0) {
					x = (j + 1) * BLOCK_SIZE;
				}
				setPosition(x + w, y + h);
			}
			if (TileMap[i][j] == 'b') {
				key = true;
				map_i = i;
				map_j = j;
			}
		}
	}
	speed.x = 0;
	speed.y = 0;
}

void Player::opening_chest() {
	TileMap[map_i][map_j] = 't';
}

class Enemy : public Entity {
private:
	int hp;
public:
	Enemy(sf::Vector2f pos, int health);
	void update(float time, sf::Vector2f pos);
	void behavior(sf::Vector2f playerPos);
	void enemyInteractionWithMap(float x, float y, float dx, float dy);
};

Enemy::Enemy(sf::Vector2f pos, int health) :
	Entity(pos, sf::Vector2i(90, 90), "G_v01.png") {
	hp = health;
	setTexturePos(sf::Vector2i(235, 0));
	void enemyInteractionWithMap(float x, float y, float dx, float dy);
	void update(float time, sf::Vector2f pos);	
}

void Enemy::update(float time, sf::Vector2f playerPos) {
	behavior(playerPos);
	move(time);
	enemyInteractionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x, speed.y);
	textureRotate(playerPos);
}

void Enemy::behavior(sf::Vector2f playerPos) {
	if ((playerPos.x - sprite.getPosition().x) < 50 && 
		(playerPos.x - sprite.getPosition().x) > 0 && 
		(playerPos.x - sprite.getPosition().x) > (playerPos.y - sprite.getPosition().y) ||
		(playerPos.y - sprite.getPosition().y) < 50 && 
		(playerPos.y - sprite.getPosition().y) > 0 && 
		(playerPos.y - sprite.getPosition().y) < (playerPos.x - sprite.getPosition().x)) {
		speed.x = 0.25;
	}
	if ((playerPos.x - sprite.getPosition().x) < 50 && 
		(playerPos.x - sprite.getPosition().x) > 0 && 
		(playerPos.x - sprite.getPosition().x) < (playerPos.y - sprite.getPosition().y) ||
		(playerPos.y - sprite.getPosition().y) < 50 && 
		(playerPos.y - sprite.getPosition().y) > 0 && 
		(playerPos.y - sprite.getPosition().y) > (playerPos.x - sprite.getPosition().x)) {
		speed.y = 0.25;
	}
	if ((playerPos.x - sprite.getPosition().x) > -50 && 
		(playerPos.x - sprite.getPosition().x) < 0 && 
		(playerPos.x - sprite.getPosition().x) < (playerPos.y - sprite.getPosition().y) ||
		(playerPos.y - sprite.getPosition().y) > -50 && 
		(playerPos.y - sprite.getPosition().y) < 0 && 
		(playerPos.y - sprite.getPosition().y) > (playerPos.x - sprite.getPosition().x)) {
		speed.x = -0.25;
	}
	if ((playerPos.x - sprite.getPosition().x) > -50 && 
		(playerPos.x - sprite.getPosition().x) < 0 && 
		(playerPos.x - sprite.getPosition().x) > (playerPos.y - sprite.getPosition().y) ||
		(playerPos.y - sprite.getPosition().y) > -50 && 
		(playerPos.y - sprite.getPosition().y) < 0 && 
		(playerPos.y - sprite.getPosition().y) < (playerPos.x - sprite.getPosition().x)) {
		speed.y = -0.25;
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
	for (int i = y / BLOCK_SIZE; i < (startY + 2 * h) / BLOCK_SIZE; i++) {
		for (int j = x / BLOCK_SIZE; j < (startX + 2 * w) / BLOCK_SIZE; j++) {
			//int j = (startX + w) / blcsize;
			if (TileMap[i][j] == '0') {
				if (dy > 0) {
					y = i * BLOCK_SIZE - 2 * h;
				}
				if (dy < 0) {
					y = (i + 1) * BLOCK_SIZE;
				}
				if (dx > 0) {
					x = j * BLOCK_SIZE - 2 * w;
				}
				if (dx < 0) {
					x = (j + 1) * BLOCK_SIZE;
				}
				setPosition(x + w, y + h);
			}
		}
	}
	speed.x = 0;
	speed.y = 0;
}