#pragma once
#include "Objects.h"

class Weapon : public Object {
	int classOfWeapon;
	int damage;
	std::string weaponName;
	sf::Vector2f attackCircle;
public:
	void interaction(sf::Vector2f playerPos);
	Weapon(sf::Vector2f position, int classOfWeapon);
	~Weapon();
	Weapon(sf::Vector2f position);
	std::string getWeaponName();
	sf::Vector2f getAttackCircle();
	int getDamage();
};

Weapon::Weapon(sf::Vector2f pos) :
	Object(pos, sf::Vector2i(94, 94)) {
	weaponName = "nothing";
	damage = 0;
	classOfWeapon = 0;
}

std::string Weapon::getWeaponName()
{
	return weaponName;
}

sf::Vector2f Weapon::getAttackCircle()
{
	return attackCircle;
}

inline int Weapon::getDamage()
{
	return damage;
}

Weapon::Weapon(sf::Vector2f pos, int cow) :
	Object(pos, sf::Vector2i(94, 94)) {
	if (cow == 1) { //меч
		setTexturePos(sf::Vector2i(0, 280), sf::Vector2i(114, 29));
		damage = 30;
		weaponName = "sword";
		attackCircle = sf::Vector2f(200, 100);
	}
	if (cow == 2) { //второй меч
		setTexturePos(sf::Vector2i(5, 345), sf::Vector2i(109, 24));
		damage = 7;
		weaponName = "second sword";
		attackCircle = sf::Vector2f(400, 20);
	}
	//if (cow == 3) { //€блоко, какое €блоко в Weapon..? kek
	//	setTexturePos(sf::Vector2i(155, 270), sf::Vector2i(39, 49));
	//	damage = 0;
	//	attackCircle = sf::Vector2f(0, 0);
	//}
	isPickedUp = false;
}

Weapon::~Weapon() {
	//std::cout << "Weapon destroyed!";
}

void Weapon::interaction(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 150) {
		text.setString("Press (Z) to take this weapon");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			isPickedUp = true;
			weaponName = "sword";
		}
	}
	else {
		text.setString("");
	}
}
