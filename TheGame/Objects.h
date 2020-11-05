#pragma once

int COUNT_OF_ITEM_TYPES = 3;
int COUNT_OF_WEAPON_TYPES = 2;

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
	isPickedUp = false;
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

struct Buff { //структура для определения бафа от предметов
	int typeOfBuff; // будет несколько типов (увеличение скорости бега/атаки, увеличение хп и тд)
	float buffScale; // нужно сделать документацию с подробными списками
};






