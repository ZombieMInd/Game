#pragma once
#include "Enemy.h"

class Object {
private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f realSize;
	sf::String file;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Object(sf::Vector2f pos, sf::Vector2f size, sf::String file);
};

Object::Object(sf::Vector2f pos, sf::Vector2f s, sf::String f) {
	file = f;
	texture.loadFromFile("assets/" + file);
	sprite.setTexture(texture);
	position = pos;
	size = s;
}
