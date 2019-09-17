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
	sf::Font font;
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
	position = pos;
	size = s;
	font.loadFromFile("assets/CyrilicOld.ttf");
	text.setFont(font);
	text.setCharacterSize(32);
	text.setPosition(pos);
}

Object::~Object() {

}

void Object::setTexturePos(sf::Vector2i pos, sf::Vector2i size) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
	//sprite.scale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setPosition(position.x, position.y);
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

std::list<Chest*> chests;
std::list<Chest*>::iterator chestIter;

Chest::Chest(sf::Vector2f pos) :
	Object(pos, sf::Vector2i(94, 94)) {
	setTexturePos(sf::Vector2i(890, 320), sf::Vector2i(94, 94));
	text.setStyle(sf::Text::Bold);
	text.setString("");
	if (chests.size() == 1) { //первый или ближайший сундук всегда с оружием
		classOfChest = 1;
	}
	else {
		classOfChest = rand() % 2 + 1;
	}
	isOpen = false;
}

void Chest::interaction(sf::Vector2f playerPos) {

	text.setString("Press (Z) to open this chest");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		chestOpening();
	}
}



void Chest::update(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 150 && isOpen == false) {
		interaction(playerPos);
	}
	else {
		text.setString("");
	}
}


class Weapon : public Object {
	int classOfWeapon;
	int damage;
public:
	void interaction(sf::Vector2f playerPos);
	Weapon(sf::Vector2f position, int classOfWeapon);
	//~Weapon();
};

Weapon::Weapon(sf::Vector2f pos, int cow) :
	Object(pos, sf::Vector2i(94, 94)) {
	if (cow == 1) { //меч
		setTexturePos(sf::Vector2i(0, 280), sf::Vector2i(114, 29));
		damage = 10;
	}
	if (cow == 2) { //второй меч
		setTexturePos(sf::Vector2i(5, 345), sf::Vector2i(109, 24));
		damage = 7;
	}
	if (cow == 3) { //яблоко
		setTexturePos(sf::Vector2i(155, 270), sf::Vector2i(39, 49));
		damage = 0;
	}
}

std::list<Object*> objects;
std::list<Object*>::iterator objIter;

void Chest::chestOpening() {
	isOpen = true;
	setTexturePos(sf::Vector2i(890, 430), getSize());
	int numOfItem = rand() % 2 + 1;
	std::cout << classOfChest << " " << numOfItem << "\n";
	if (classOfChest == 1) {
		objects.push_back(new Weapon(position, numOfItem));
	}
	if (classOfChest == 2) {
		objects.push_back(new Weapon(position, 3));
	}
}

void Weapon::interaction(sf::Vector2f playerPos) {

}



class PassiveItem : public Object {
private:

};

