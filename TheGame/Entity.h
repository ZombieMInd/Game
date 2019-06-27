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
	sf::Vector2f speed;
	sf::Sprite sprite;
	Entity(sf::Vector2i pos, sf::Vector2i s, sf::String f);
	~Entity();
	void setTexturePos(sf::Vector2i pos);
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
}


Entity::~Entity()
{
}

void Entity::setTexturePos(sf::Vector2i pos) {
	sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
	sprite.scale(sf::Vector2f(0.112, 0.112));
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