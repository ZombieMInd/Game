#pragma once
#include "Objects.h"

class PassiveItem : public Object {
private:
public:
	~PassiveItem();
	Buff buff;
	PassiveItem(sf::Vector2f pos, int coi);
	void interaction(sf::Vector2f playerPos);
};

PassiveItem::PassiveItem(sf::Vector2f pos, int coi) :
	Object(pos, sf::Vector2i(94, 94)) {
	if (coi == 1) { //������
		setTexturePos(sf::Vector2i(155, 270), sf::Vector2i(39, 49));
		buff.typeOfBuff = 1;
		buff.buffScale = 0.7f;
	}
	if (coi == 2) { //�����
		setTexturePos(sf::Vector2i(155, 345), sf::Vector2i(44, 34));
		buff.typeOfBuff = 2;//��������+
		buff.buffScale = 0.5f;
	}
	if (coi == 3) { //����
		setTexturePos(sf::Vector2i(235, 285), sf::Vector2i(59, 29));
		buff.typeOfBuff = 3;//������+?
		buff.buffScale = 0.1f;
	}
	isPickedUp = false;
}


PassiveItem::~PassiveItem() {
	//std::cout << "Object destroyed" << "\n";
	//delete this;
}

void PassiveItem::interaction(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 150) {
		text.setString("Press (Z) to take this item");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			isPickedUp = true;
		}
	}
	else {
		text.setString("");
	}
}