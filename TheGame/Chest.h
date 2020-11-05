#pragma once
#include "Objects.h"

class Chest : public Object {
	unsigned int classOfChest; //будут несколько типов сундуков
	bool isOpen;
	bool isGained;
	sf::Clock openTimer;
	int chestSize;
public:
	Chest(sf::Vector2f position);
	void objectGain();
	void interaction(sf::Vector2f playerPos);
	void chestOpening();
	void update(sf::Vector2f playerPos);
	void setChestSize(int);
};

Chest::Chest(sf::Vector2f pos) :
	Object(pos, sf::Vector2i(94, 94)) {
	setTexturePos(sf::Vector2i(890, 320), sf::Vector2i(94, 94));
	text.setStyle(sf::Text::Bold);
	text.setString("");
	if (chestSize == 1) { //первый или ближайший сундук всегда с оружием
		classOfChest = 1;
	}
	else {
		classOfChest = rand() % 2 + 1;
	}
	isOpen = false;
	isGained = false;
}

void Chest::interaction(sf::Vector2f playerPos) {

	text.setString("Press (Z) to open this chest");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		chestOpening();
	}
}


void Chest::setChestSize(int size) {
	chestSize = size;
}
void Chest::update(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 100 && isOpen == false) {
		interaction(playerPos);
	}
	else {
		text.setString("");
	}
	if (openTimer.getElapsedTime().asMilliseconds() >= 500 && isOpen && isGained == false) {
		objectGain();
	}
}

void Chest::chestOpening() {
	isOpen = true;
	setTexturePos(sf::Vector2i(890, 430), getSize());
	openTimer.restart();
}

std::list<Weapon*> weapons;
std::list<Weapon*>::iterator wepIter;
std::list<PassiveItem*> items;
std::list<PassiveItem*>::iterator itemIter;

void Chest::objectGain() {
	int numOfItem = rand() % 2 + 1;
	std::cout << classOfChest << " " << numOfItem << "\n";
	if (classOfChest == 1) {
		weapons.push_back(new Weapon(position, numOfItem));
	}
	if (classOfChest == 2) {
		items.push_back(new PassiveItem(position, rand() % 3 + 1));
	}
	isGained = true;
}