#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
//#include "map.h"
//#include "view.h"

using namespace sf;
// размер персонажа
//const int BLOCK_SIZE = 90;
//bool key = false;

/*void interactionWithMap(Entity& player, float x, float y, float dx, float dy) {
	float h, w;
	h = player.getRealSize().y / 2;
	w = player.getRealSize().x / 2;
	y -= h;
	x -= w;
	float startX = x;
	float startY = y;
	for (int i = y / BLOCK_SIZE; i < (startY + 2 * h) / BLOCK_SIZE; i++) {
		for (int j = x / BLOCK_SIZE; j < (startX + 2 * w) / BLOCK_SIZE; j++) {
			//int j = (startX + w) / blcsize;
			if (TileMap[i][j] == '0') {
				if (dy > 0) {
					y = i * BLOCK_SIZE - 2 * h;
				}
				if (dy < 0) {
					y = (i + 1) * BLOCK_SIZE;
				}
				if (dx > 0) {
					x = j * BLOCK_SIZE - 2 * w;
				}
				if (dx < 0) {
					x = (j + 1) * BLOCK_SIZE;
				}
				player.setPosition(x + w, y + h);
			}
			if (TileMap[i][j] == 'b') {
				key = true;
				map_i = i;
				map_j=j;
			}
		}
	}
}*/

/*void opening_chest() {
	TileMap[map_i][map_j] = 't';
}*/

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	float CurrentFrame = 0;
	sf::Clock clock;
	Player player(sf::Vector2f(150, 150), 100);
	Image map_image;
	map_image.loadFromFile("assets/G_v01.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	Font font;
	font.loadFromFile("assets/CyrilicOld.ttf");
	Text text("", font, 32);

	while (window.isOpen())
	{
		//дл€ плавности и контрол€ игрока
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

		//sf::Vector2f v(0, 0);
		
		//GetPlayerCoordinateForView(v.x, v.y);
		window.clear();

		// прорисовка карты (в отдельный модуль)
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == ' ') {
					s_map.setTextureRect(IntRect(360, 0, 90, 90));
				}
				if (TileMap[i][j] == 'b') {
					s_map.setTextureRect(IntRect(470, 0, 90, 90));
				}
				if (TileMap[i][j] == 't') {
					s_map.setTextureRect(IntRect(470, 129, 90, 90));
				}
				if ((TileMap[i][j] == '0')) {
					s_map.setTextureRect(IntRect(0, 0, 90, 90));
				}
				//s_map.scale(sf::Vector2f(0.112, 0.112));
				s_map.setPosition(j * 90, i * 90);
				window.draw(s_map);
			}
		}

		//window.draw(s_map);
		//player.controle();
		//float dx = player.speed.x;
		//float dy = player.speed.y;
		//v = player.sprite.getPosition();
		//player.move(time);
		//v = player.sprite.getPosition();
		//interactionWithMap(player, v.x, v.y, dx, dy);

		// работа с текстом (надо ее в отдельный модуль пихнуть) 
		// загрузка шрифта была в цикле, ай-€й-€й! нехорошо 
		//text.setColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		if (key) {
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
		window.draw(text);
		window.setView(view);
		player.update(time, pos);
		//player.textureRotate(pos);
		window.draw(player.sprite);
		window.display();
	}
	//system("pause");
	return EXIT_SUCCESS;

}