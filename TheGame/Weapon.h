#pragma once
#include "Objects.h"

class Weapon : public Object {
	int classOfWeapon;
	int damage;
	sf::String weaponName;
public:
	void interaction(sf::Vector2f playerPos);
	Weapon(sf::Vector2f position, int classOfWeapon);
	~Weapon();
	Weapon(sf::Vector2f position);
	sf::String getWeaponName();
};



Weapon::Weapon(sf::Vector2f pos) :
	Object(pos, sf::Vector2i(94, 94)) {
	weaponName = "nothing";
	damage = 0;
	classOfWeapon = 0;
}

Weapon::Weapon(sf::Vector2f pos, int cow) :
	Object(pos, sf::Vector2i(94, 94)) {
	if (cow == 1) { //меч
		setTexturePos(sf::Vector2i(0, 280), sf::Vector2i(114, 29));
		damage = 10;
		weaponName = "sword";
	}
	if (cow == 2) { //второй меч
		setTexturePos(sf::Vector2i(5, 345), sf::Vector2i(109, 24));
		damage = 7;
		weaponName = "second sword";
	}
	if (cow == 3) { //€блоко, какое €блоко в Weapon..?
		setTexturePos(sf::Vector2i(155, 270), sf::Vector2i(39, 49));
		damage = 0;
	}
	isPickedUp = false;
}

//sf::String Weapon::getWeaponName() {
//	return weaponName;
//}

Weapon::~Weapon() {
	std::cout << "Weapon destroyed!";
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
