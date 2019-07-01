#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

using namespace sf;


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

	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			if ((TileMap[i][j] == 'e')) {
				entities.push_back(new Enemy(Vector2f((j - 0.5) * BLOCK_SIZE, (i - 0.5) * BLOCK_SIZE), 100));
			}
		}
	}
	while (window.isOpen())
	{
		//��� ��������� � �������� ������
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

		// ���������� ����� (� ��������� ������)
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

		// ������ � ������� (���� �� � ��������� ������ �������) 
		// �������� ������ ���� � �����, ��-��-��! �������� 
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

		for (iter = entities.begin(); iter != entities.end(); iter++) {
			(*iter)->update(time, player.sprite.getPosition());
			window.draw((*iter)->sprite);
		}


		window.draw(player.sprite);
		window.display();
	}
	//system("pause");
	return EXIT_SUCCESS;

}