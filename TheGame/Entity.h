#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
	sf::Vector2i position;
	sf::Vector2i size;
	int height;
	int width;
	sf::String file;
	sf::Texture texture;
	sf::Vector2f posOld;
	sf::Vector2f direction;
	float rotOld;

public:
	sf::Vector2f speed;
	sf::Sprite sprite;
	Entity(sf::Vector2i pos, sf::Vector2i s, sf::String f);
	~Entity();
	void setTexturePos(sf::Vector2i pos);
	void textureRotate(sf::Vector2f pos);
	void move(float time);
};


Entity::Entity(sf::Vector2i pos, sf::Vector2i s, sf::String f)
{
	file = f;
	texture.loadFromFile("assets/" + file);
	sprite.setTexture(texture);
	position = pos;
	size = s;
	speed = sf::Vector2f(0, 0);
	posOld = sf::Vector2f(0, 0);
	direction = sf::Vector2f(0, 1);
	rotOld = 0;
	sprite.setPosition(position.x, position.y);
}


Entity::~Entity()
{
}

void Entity::setTexturePos(sf::Vector2i pos) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
	sprite.scale(sf::Vector2f(0.112, 0.112));
	sprite.setOrigin(size.x / 2, size.y / 2);
}

void Entity::textureRotate(sf::Vector2f pos) {
	sf::Vector2f dir;
	if (abs(pos.x - posOld.x) > 0.005 || abs(pos.y - posOld.y) > 0.005) {
		sprite.setRotation(0);
		dir.x = pos.x - position.x;
		dir.y = pos.y - position.y;
		float rotation = (atan2(dir.y, dir.x) * 180. / 3.14159265);
		//std::cout << rotation << " " <<  std::endl;
		sprite.rotate(rotation);
	}
}


void Entity::move(float time) {
	position.x += speed.x * time;
	position.y += speed.y * time;
	speed.x = 0;
	speed.y = 0;
	sprite.setPosition(position.x, position.y);
}

class Player : public Entity {
private:
	int hp;

public:
	Player(sf::Vector2i pos, int health);
	void controle();
};

Player::Player(sf::Vector2i pos, int health):
	Entity(pos, sf::Vector2i(89, 89), "G_v01.png"){
	hp = health;
	setTexturePos(sf::Vector2i(235, 100));
	
}

void Player::controle() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		speed.y = -0.1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		speed.y = 0.1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		speed.x = -0.1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		speed.x = 0.1;
	}
}