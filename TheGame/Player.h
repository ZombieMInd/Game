#pragma once
#include "Entity.h"
#include "Objects.h"
#include "PassiveItem.h"
#include "Weapon.h"

class Player : public Entity {
private:
	double hp;
	sf::Vector2f attackCircle;//первая координата - r радиус поражения, вторая fi - угол поражения
	//std::string weapon;
	Weapon* weapon;
	sf::Clock attackTimer; //таймер засекающий время между ударами
	sf::Clock changeSpriteTimer;
	int attackSpeed; //кол-во милсек до следующего удара
	int animationFrame;
	int damage;
	float speedScale;
	std::list<Entity*> entities;
public:
	Player(sf::Vector2f pos, int health);
	Player();
	~Player();
	void controle();
	void update(float time, sf::Vector2f pos);
	void interactionWithMap(float x, float y, float dx, float dy);
	void opening_chest();
	void setAttackCircle();
	void setDamage();
	void makeDamage(int damage);
	int getHP();
	void attackAnimation();
	void pickUpItem(PassiveItem* item);
	void pickUpWeapon(Weapon* wep);
	void displayStat();
	bool isAlive();
	void setEntities(std::list<Entity*> entities);
};

Player::Player(sf::Vector2f pos, int health) :
	Entity(pos, sf::Vector2f(45, 45), "PersNew.png") {
	hp = health;
	setTexturePos(sf::Vector2i(0, 0), sf::Vector2i(137, 254));
	setOrigin(25, 132);
	attackSpeed = 600;
	attackCircle = sf::Vector2f(0, 0);
	animationFrame = 0;
	speedScale = 1.0f;
}

Player::Player()
{
}

Player::~Player()
{

}

void Player::controle() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		speed.y = -0.3f * speedScale;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
		speed.y = 0.3f * speedScale;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		speed.x = -0.3f * speedScale;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
		speed.x = 0.3f * speedScale;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		int timePassed = attackTimer.getElapsedTime().asMilliseconds();
		if (timePassed >= attackSpeed) {
			setAttacking(true);
			attackTimer.restart();
			//
			std::cout << getAngel(sf::Vector2f(1000, 1000)) << " " << distanceTo(sf::Vector2f(1000, 1000)) << std::endl;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		displayStat();
	}
}

void Player::update(float time, sf::Vector2f pos) {
	if (changeSpriteTimer.getElapsedTime().asMilliseconds() > 100 && hp < 100) {
		sprite.setColor(sf::Color::White);
	}
	
	GetPlayerCoordinateForView(sprite.getPosition().x, sprite.getPosition().y);
	controle();
	attackAnimation();
	move(time);
	interactionWithMap(sprite.getPosition().x, sprite.getPosition().y, speed.x*time, speed.y*time);
	textureRotate(pos);
	if (hp < 100) {
		hp += 0.01;
		//std::cout << "Hp now: " << hp << std::endl;
	}
	
	/*if (weapon != nullptr) {
		setAttackCircle();
	}*/
	
	if (getAttacking()) {
		for (auto ent : entities) {
			/*std::cout << "Dist to ent " << distanceTo(ent->getPos()) << std::endl;
			std::cout << "Angel to ent " << getAngel(ent->getPos()) << std::endl;
			std::cout << "Dir " << getDir() << std::endl;*/
			if (distanceTo(ent->getPos()) <= attackCircle.x &&
				getAngel(ent->getPos()) < getDir() + attackCircle.y &&
				getAngel(ent->getPos()) > getDir() - attackCircle.y)
				ent->makeDamage(damage);
			//std::cout << ent->getHP() << std::endl;
		}
		setAttacking(false);
	}
}

void Player::interactionWithMap(float x, float y, float dx, float dy) {
	float h, w;
	h = getRealSize().y / 2;
	w = getRealSize().x / 2;
	y -= h;
	x -= w;
	float startX = x;
	float startY = y;
	float newX;
	float oldX = x - dx;
	float oldY = y - dy;
	int j = dx <= 0 ? x / BLOCK_SIZE : (startX + 2 * w) / BLOCK_SIZE;
	if (dx != 0) {
		for (int i = y / BLOCK_SIZE; i < (startY + 2 * h) / BLOCK_SIZE; i++) {
			if (TileMap[i][j] == '0') {
				if (dx > 0 && TileMap[i][j - 1] != '0' && oldX <= j * BLOCK_SIZE - 2 * w) {
					x = j * BLOCK_SIZE - 2 * w;
					break;
				}
				if (dx < 0 && TileMap[i][j + 1] != '0' && oldX >= (j + 1) * BLOCK_SIZE) {
					x = (j + 1) * BLOCK_SIZE;
					break;
				}
			}
		}
		setPosition(x + w, y + h);
	}
	int i = dy <= 0 ? y / BLOCK_SIZE : (startY + 2 * h) / BLOCK_SIZE;
	if (dy != 0) {
		for (int j = x / BLOCK_SIZE; j < (startX + 2 * w) / BLOCK_SIZE; j++) {
			if (TileMap[i][j] == '0') {
				if (dy > 0 && TileMap[i - 1][j] != '0' && oldY <= i * BLOCK_SIZE - 2 * h) {
					y = i * BLOCK_SIZE - 2 * h;
					break;
				}
				if (dy < 0 && TileMap[i + 1][j] != '0' && oldY >= (i + 1) * BLOCK_SIZE) {
					y = (i + 1) * BLOCK_SIZE;
					break;
				}
			}
		}
		setPosition(x + w, y + h);
	}
	if (TileMap[i][j] == 'b') {
		key = true;
		map_i = i;
		map_j = j;
	}
	speed.x = 0;
	speed.y = 0;
}

void Player::opening_chest() {
	TileMap[map_i][map_j] = 't';
	//weapon = "sword";
	sprite.setTextureRect(sf::IntRect(0, 365, 90, 455));
}

void Player::setAttackCircle() {
	if (weapon != nullptr)
		attackCircle = weapon->getAttackCircle();
}

inline void Player::setDamage()
{
	damage = weapon->getDamage();
}

void Player::makeDamage(int damage) {
	hp -= damage;
	sprite.setColor(sf::Color(255, 0, 0, 100));
	changeSpriteTimer.restart();
}

int Player::getHP() {
	return hp;
}

void Player::attackAnimation() {
	if (attackTimer.getElapsedTime().asMilliseconds() < 10) {
		animationFrame = 1;
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 50 &&
		attackTimer.getElapsedTime().asMilliseconds() < 100) {
		animationFrame = 2;
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 100 &&
		attackTimer.getElapsedTime().asMilliseconds() < 200) {
		animationFrame = 3;
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 200 &&
		attackTimer.getElapsedTime().asMilliseconds() < 250) {
		animationFrame = 4;
	}
	if (attackTimer.getElapsedTime().asMilliseconds() > 250) {
		animationFrame = 0;
	}
	setTextureForAnimation(sf::Vector2i(145 * animationFrame, 0), sf::Vector2i(137, 254));
}

void Player::pickUpItem(PassiveItem* item) {
	if (item->buff.typeOfBuff == 1) {
		hp += item->buff.buffScale;
	}
	if (item->buff.typeOfBuff == 2) {
		speedScale += item->buff.buffScale;
	}
	if (item->buff.typeOfBuff == 1) {
		attackSpeed *= 1.0f + item->buff.buffScale;
	}
}

void Player::pickUpWeapon(Weapon* wep) {
	std::cout << "Weapon: " << wep->getWeaponName() << "\n";
	weapon = wep;
	setAttackCircle();
	setDamage();
}

void Player::displayStat() {
	std::cout << "Speed: " << speedScale << "\nAttackSpeed: " << attackSpeed << "\nHP: " << hp << "\n";
}
bool Player::isAlive() {
	return hp > 0;
}

void Player::setEntities(std::list<Entity*> entities) {
	this->entities = entities;
}
