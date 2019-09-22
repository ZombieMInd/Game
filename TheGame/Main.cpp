#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy.h"
using namespace sf;


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	float CurrentFrame = 0;
	sf::Clock clock;
	Player player(sf::Vector2f(200, 200), 100);
	Image map_image;
	map_image.loadFromFile("assets/G_v06.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	Font font;
	font.loadFromFile("assets/CyrilicOld.ttf");
	Text text("", font, 32);
	// как это работает?
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			if ((TileMap[i][j] == 'e')) {
				Enemy *enemy = new Enemy(Vector2f((j - 0.5) * BLOCK_SIZE, (i - 0.5) * BLOCK_SIZE), 100, " ");
				enemy->setPlayer(player);
				entities.push_back(enemy);
			}
			if (TileMap[i][j] == 'b') {
				chests.push_back(new Chest(Vector2f((j + 0.5) * BLOCK_SIZE, (i + 0.5) * BLOCK_SIZE)));
			}
		}
	}
	

	while (window.isOpen())
	{
		//для плавности и контроля игрока
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		//draw_map(s_map);
		// прорисовка карты (в отдельный модуль)
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == ' ') {
					s_map.setTextureRect(IntRect(890, 65, 94, 94));
				}
				if (TileMap[i][j] == 't') {
					s_map.setTextureRect(IntRect(890, 430, 94, 94));
				}
				if ((TileMap[i][j] == '0')) {
					s_map.setTextureRect(IntRect(890, 180, 94, 209));
				}
				s_map.setPosition(j * 94, i * 94);
				window.draw(s_map);
			}
		}
		for (auto chest : chests) {
			window.draw(chest->sprite);
		}
		for (auto item : items) {
			window.draw(item->sprite);
		}
		for (auto wep : weapons) {
			window.draw(wep->sprite);
		}

		
		/*if (key) {
			text.setString("Press (Z) to open this chest");
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				player.opening_chest();
			}
		}
		else {
			text.setString("");
		}
		key = false;
		text.setPosition(player.sprite.getPosition().x + 45, player.sprite.getPosition().y);
		window.draw(text);*/
		window.setView(view);
		
		player.update(time, pos);
		window.draw(player.sprite);

		for (iter = entities.begin(); iter != entities.end();) {
			Entity *enemy = *iter;
			enemy->update(time, player.getPos());
			if (enemy->getHP() <= 0) {
				iter = entities.erase(iter);
				delete enemy;
			}
			else iter++;
		}

		for (chestIter = chests.begin(); chestIter != chests.end();) {
			Chest* chest = *chestIter;
			chest->update(player.getPos());
			window.draw(chest->text);
			chestIter++;
		}

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

		for (auto ent : entities) {
			window.draw(ent->sprite);
		}

		
		
		
		window.display();
	}
	return EXIT_SUCCESS;
}