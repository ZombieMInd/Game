#pragma once
//#include "Enemy.h"

class Object {
private:
	sf::Vector2i size;
	sf::Vector2f realSize;
	sf::String file;
	sf::Texture texture;
	
public:
	bool isPickedUp;
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
	bool isPickedUp = false;
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

struct Buff { //структура для определения бафа от предметов
	int typeOfBuff; // будет несколько типов (увеличение скорости бега/атаки, увеличение хп и тд)
	float buffScale; // нужно сделать документацию с подробными списками
};

class Weapon : public Object {
	int classOfWeapon;
	int damage;
public:
	void interaction(sf::Vector2f playerPos);
	Weapon(sf::Vector2f position, int classOfWeapon);
	~Weapon();
};

class PassiveItem : public Object {
private:
public:
	~PassiveItem();
	Buff buff;
	PassiveItem(sf::Vector2f pos, int coi);
	void interaction(sf::Vector2f playerPos);
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
	isPickedUp = false;
}

Weapon::~Weapon() {
	std::cout << "Weapon destroyed!";
}

std::list<Weapon*> weapons;
std::list<Weapon*>::iterator wepIter;
std::list<PassiveItem*> items;
std::list<PassiveItem*>::iterator itemIter;

void Chest::chestOpening() {
	isOpen = true;
	setTexturePos(sf::Vector2i(890, 430), getSize());
	openTimer.restart();
}

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

void Weapon::interaction(sf::Vector2f playerPos) {
	if (distanceTo(playerPos) <= 150) {
		text.setString("Press (Z) to take this weapon");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			isPickedUp = true;
		}
	}
	else {
		text.setString("");
	}
	
}


PassiveItem::PassiveItem(sf::Vector2f pos, int coi):
	Object(pos, sf::Vector2i(94, 94)) {
	if (coi == 1) { //яблоко
		setTexturePos(sf::Vector2i(155, 270), sf::Vector2i(39, 49));
		buff.typeOfBuff = 1;
		buff.buffScale = 100;
	}
	if (coi == 2) { //сапог
		setTexturePos(sf::Vector2i(155, 345), sf::Vector2i(44, 34));
		buff.typeOfBuff = 2;//скорость+
		buff.buffScale = 0.5f;
	}
	if (coi == 3) { //очки
		setTexturePos(sf::Vector2i(235, 285), sf::Vector2i(59, 29));
		buff.typeOfBuff = 3;//зрение+?
		buff.buffScale = 0.1f;
	}
	isPickedUp = false;
}

PassiveItem::~PassiveItem() {
	std::cout << "Object destroyed" << "\n";
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