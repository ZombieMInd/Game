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
	

public:
	sf::Vector2i speed;
	sf::Sprite sprite;
	Entity(sf::Vector2i pos, sf::Vector2i s, sf::String f);
	~Entity();
	void setTexturePos(sf::Vector2i pos);
	void move(sf::Vector2i speed, float time);
};


Entity::Entity(sf::Vector2i pos, sf::Vector2i s, sf::String f)
{
	file = f;
	texture.loadFromFile("assets/" + file);
	sprite.setTexture(texture);
	position = pos;
	size = s;
	speed = sf::Vector2i(0, 0);
}


Entity::~Entity()
{
}

void Entity::setTexturePos(sf::Vector2i pos) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, width, height));
}

void Entity::move(sf::Vector2i speed, float time) {
	position.x += speed.x * time;
	position.y += speed.y * time;
	speed = sf::Vector2i(0, 0);
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
		speed.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		speed.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		speed.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		speed.x = 1;
	}
}