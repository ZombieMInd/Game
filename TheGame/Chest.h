#pragma once
#include "Objects.h"

class Chest : public Object {
	unsigned int classOfChest; //����� ��������� ����� ��������
	bool isOpen;
	bool isGained;
	sf::Clock openTimer;
	int chestSize;
public:
	Chest(sf::Vector2f position);

	void interaction(sf::Vector2f playerPos);
	void chestOpening();
	void update(sf::Vector2f playerPos);
	void setChestSize(int);
	int checkOfOpened();

	Weapon* weaponGain();
	PassiveItem* passiveItemGain();
};

Chest::Chest(sf::Vector2f pos) :
	Object(pos, sf::Vector2i(94, 94)) {
	setTexturePos(sf::Vector2i(890, 320), sf::Vector2i(94, 94));
	text.setStyle(sf::Text::Bold);
	text.setString("");
	if (chestSize == 1) { //������ ��� ��������� ������ ������ � �������
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

int Chest::checkOfOpened()
{
	if (openTimer.getElapsedTime().asMilliseconds() >= 500 && isOpen && isGained == false) {
		return classOfChest;
	}
	else {
		return 0;
	}
}

void Chest::update(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 100 && isOpen == false) {
		interaction(playerPos);
	}
	else {
		text.setString("");
	}
}

void Chest::chestOpening() {
	isOpen = true;
	setTexturePos(sf::Vector2i(890, 430), getSize());
	openTimer.restart();
}

Weapon* Chest::weaponGain() {
	int numOfItem = rand() % 2 + 1;
	isGained = true;
	return new Weapon(position, numOfItem);
}

inline PassiveItem* Chest::passiveItemGain()
{
	int numOfItem = rand() % 3 + 1;
	isGained = true;
	return new PassiveItem(position, numOfItem);
}
