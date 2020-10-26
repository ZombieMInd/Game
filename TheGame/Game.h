#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

using namespace sf;
class Game{
private:
	//string state;
	int gameLevel;
	int levelOfComplexity; // easy, medium, hard. depends on amount of enemy, weapons etc
	std::list<Entity*> entities;
	std::list<Chest*> chests;
protected:
	Clock clock;
	Image map_image;
	Texture map;
	Sprite s_map;
	Font font;
	Text text;
public:
	Game();
	Game(int, int);
	void init();
	void play();
	void generatingObjectsOnMap(Player&);
	void drawMap(RenderWindow&);
	void updateEntities(Player&, float&);
	void updateChests(Player&, RenderWindow&);
};

Game::Game() {
	gameLevel = 1;
	levelOfComplexity = 1;
}

Game::Game(int gameLevel, int levelOfComplexity) {
	this->gameLevel = gameLevel;
	this->levelOfComplexity = levelOfComplexity;
}

void Game::init() {
	map_image.loadFromFile("assets/G_v06.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);
	font.loadFromFile("assets/CyrilicOld.ttf");
	text.setFont(font);
	text.setCharacterSize(40);
	text.setPosition(view.getCenter());
}

void Game::generatingObjectsOnMap(Player &player) {
	int chestCount = 0;
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			if ((TileMap[i][j] == 'e')) {
				Enemy *enemy = new Enemy(Vector2f((j - 0.5) * BLOCK_SIZE, (i - 0.5) * BLOCK_SIZE), 100, " ");
				enemy->setPlayer(&player);
				entities.push_back(enemy);
			}
			if (TileMap[i][j] == 'b') {
				chests.push_back(new Chest(Vector2f((j + 0.5) * BLOCK_SIZE, (i + 0.5) * BLOCK_SIZE)));
				chestCount++;
			}
		}
	}
	for (auto chest : chests) {
		chest->setChestSize(chestCount);
	}
}

void Game::drawMap(RenderWindow &window) {
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			if (TileMap[i][j] == ' ') {
				this->s_map.setTextureRect(IntRect(890, 65, 94, 94));
			}
			if (TileMap[i][j] == 't') {
				this->s_map.setTextureRect(IntRect(890, 430, 94, 94));
			}
			if ((TileMap[i][j] == '0')) {
				this->s_map.setTextureRect(IntRect(890, 180, 94, 209));
			}
			this->s_map.setPosition(j * 94, i * 94);
			window.draw(this->s_map);
		}
	}
}

void Game::updateChests(Player& player, RenderWindow &window) {
	for (std::list<Chest*>::iterator chestIter = chests.begin(); chestIter != chests.end();) {
		Chest* chest = *chestIter;
		chest->update(player.getPos());
		window.draw(chest->text);
		chestIter++;
	}
}

void Game::updateEntities(Player& player, float& time) {
	for (std::list<Entity*>::iterator iter = entities.begin(); iter != entities.end();) {
		Entity *enemy = *iter;
		enemy->update(time, player.getPos());
		if (enemy->getHP() <= 0) {
			iter = entities.erase(iter);
			delete enemy;
		}
		else iter++;
	}
}
void Game::play() {
	RenderWindow window(sf::VideoMode(800, 600), "Kill all bad dogs 2");

	Player player(sf::Vector2f(200, 200), 100);
	
	generatingObjectsOnMap(player);
	player.setEntities(entities);
	float time;
	while (window.isOpen()) {

		//для плавности и контроля игрока
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;
		//sf::sleep(sf::milliseconds(2));

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		drawMap(window);

		for (auto chest : chests) {
			window.draw(chest->sprite);
		}
		for (auto item : items) {
			window.draw(item->sprite);
		}
		for (auto wep : weapons) {
			window.draw(wep->sprite);
		}

		window.setView(view);

		if (player.isAlive()) {
			player.update(time, pos);
			window.draw(player.sprite);

			updateEntities(player, time);

			updateChests(player, window);


			for (wepIter = weapons.begin(); wepIter != weapons.end();) {
				Weapon* wep = *wepIter;
				wep->interaction(player.getPos());
				if (wep->isPickedUp) {
					player.pickUpWeapon(wep);
					wepIter = weapons.erase(wepIter);
					delete wep;
				}
				else {
					window.draw(wep->text);
					wepIter++;
				}
			}

			for (itemIter = items.begin(); itemIter != items.end();) {
				PassiveItem* item = *itemIter;
				item->interaction(player.getPos());
				if (item->isPickedUp) {
					player.pickUpItem(item);
					itemIter = items.erase(itemIter);
					delete item;
				}
				else {
					window.draw(item->text);
					itemIter++;
				}
			}
		}
		else {
			text.setString("GAME OVER! press r to restart");
			text.setPosition(view.getCenter());
			window.draw(text);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				std::cout << "lol";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

		}

		for (auto ent : entities) {
			window.draw(ent->sprite);
		}
		window.display();
	}
}