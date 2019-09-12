#pragma once
#include "Enemy.h"

class Object {
private:
	sf::Vector2i size;
	sf::Vector2f realSize;
	sf::String file;
	sf::Texture texture;
	
public:
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Text text;
	Object(sf::Vector2f pos, sf::Vector2i size);
	~Object();
	virtual void interaction(sf::Vector2f playerPos) = 0;
	void setTexturePos(sf::Vector2i position, sf::Vector2i size);
	float distanceTo(sf::Vector2f pos);
	sf::Vector2i getSize();
};

Object::Object(sf::Vector2f pos, sf::Vector2i s) {
	texture.loadFromFile("assets/G_v06.png");
	sprite.setTexture(texture);
	setTexturePos(sf::Vector2i(890, 320), size);
	position = pos;
	size = s;
}

Object::~Object() {

}

void Object::setTexturePos(sf::Vector2i pos, sf::Vector2i size) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
	sprite.scale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
	sprite.setOrigin(size.x / 2, size.y / 2);
}

sf::Vector2i Object::getSize() {
	return size;
}

float Object::distanceTo(sf::Vector2f pos) {
	sf::Vector2f dir;
	dir.x = pos.x - position.x;
	dir.y = pos.y - position.y;
	return sqrtf(dir.x * dir.x + dir.y * dir.y);
}

class Chest : public Object {
	unsigned int classOfChest; //будут несколько типов сундуков
	bool isOpen;
public:
	Chest(sf::Vector2f position);
	void interaction(sf::Vector2f playerPos);
	void chestOpening();
	void update(sf::Vector2f playerPos);
};

Chest::Chest(sf::Vector2f pos) :
	Object(pos, sf::Vector2i(94, 94)) {
	text.setString("");
	isOpen = false;
}

void Chest::interaction(sf::Vector2f playerPos) {

	text.setString("Press (Z) to open this chest");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		chestOpening();
	}
	text.setPosition(position.x + 45, position.y);
}

void Chest::chestOpening() {
	isOpen = true;
	setTexturePos(sf::Vector2i(890, 430), getSize());
}

void Chest::update(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 150) {
		interaction(playerPos);
	}
	else {
		text.setString("");
	}
}

std::list<Chest*> chests;
std::list<Chest*>::iterator chestIter;

class Weapon : public Object {

};

class PassiveItem : public Object {

};