#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "map.h"
#include "view.h"
#include <math.h>

const int BLOCK_SIZE = 94;
bool key = false;

const float PLAYER_SCALE = 0.8f;
class Entity
{
	sf::Vector2f position;
	sf::Vector2i size;
	sf::Vector2f realSize;
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
	Entity();
	Entity(sf::Vector2f pos, sf::Vector2f size, sf::String file);
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
	virtual void makeDamage(int damage) = 0;
	virtual int getHP() = 0;
	float getAngel(sf::Vector2f pos);
	sf::Vector2f getSpeed(sf::Vector2f pos);
	float distanceTo(sf::Vector2f pos);
	float getDir();
	void setOrigin(float x, float y);
};

std::list<Entity*> entities;
std::list<Entity*>::iterator iter;

Entity::Entity(){

}

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


Entity::~Entity(){
<<<<<<< HEAD
=======
	//delete this;
>>>>>>> origin/enemyattack
}

void Entity::setTexturePos(sf::Vector2i pos, sf::Vector2i size) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
	sprite.scale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
	sprite.setOrigin((float)size.x / 2, (float)size.y / 2);
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
