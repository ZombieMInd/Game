#pragma once
#include "Enemy.h"

class Object {
private:
	sf::Vector2i size;
	sf::Vector2f realSize;
	sf::String file;
	sf::Texture texture;
	sf::Sprite sprite;

protected:
	sf::Vector2f position;
	sf::Font font;
	sf::Text text;
	sf::RenderWindow *wnd;
public:
	Object(sf::Vector2f pos, sf::Vector2i size);
	~Object();
	virtual void interaction(sf::Vector2f playerPos) = 0;
	void setTexturePos(sf::Vector2i position, sf::Vector2i size);
	float distanceTo(sf::Vector2f pos);
	sf::Vector2i getSize();
	void setWindow(sf::RenderWindow *window);
	sf::Text * getText() {
		return &text;
	}
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
	float tt= sqrtf(dir.x * dir.x + dir.y * dir.y);
	return tt;
}

void Object::setWindow(sf::RenderWindow *window) {
	wnd = window;
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
		font.loadFromFile("assets/CyrilicOld.ttf");
		text.setFont(font);
		text.setCharacterSize(32);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		isOpen = false;
}

void Chest::interaction(sf::Vector2f playerPos) {

	text.setString("Press (Z) to open this chest");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		chestOpening();
	}
	text.setPosition(position.x + 115, position.y+90);
	wnd->draw(text);
}

void Chest::chestOpening() {
	isOpen = true;
	setTexturePos(sf::Vector2i(890, 430), getSize());
	// мы сюда попадаем, но это не работает. чекни
	// раньше мы из main это делали и в классе player было все прописано
	//сейчас нет, посмотри это
	//
}

void Chest::update(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 175) {
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