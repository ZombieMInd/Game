#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "map.h"
#include "view.h"
using namespace sf;
// ������ ���������
const float h = 5;
const float w = 5;

void interactionWithMap(float x, float y, float dx, float dy){
	Player player1(sf::Vector2f(150, 150), 100);//�-��� �������������� � ������
	for (int i = y / 90; i < (y + h) / 90; i++) {//���������� �� ��������, �������������� � �������,, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = x / 90; j < (x + w) / 90; j++){//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			if (TileMap[i][j] == '0'){//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				if (dy > 0){
					y = i * 90 - h;
					player1.setPosition(x, y);
				}
				if (dy < 0){
					y = i * 90 + 90;
					player1.setPosition(x, y);
				}
				if (dx > 0){
					x = j * 90 - w;
					player1.setPosition(x, y);
				}
				if (dx < 0){
					x = j * 90 + 90;
					player1.setPosition(x, y);
				}
			}
			if (TileMap[i][j] == 'b') { //���� ������ ����� 's' (������)

				TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
			}
		}
	}
}


int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	float CurrentFrame = 0;
	sf::Clock clock;
	Player player(sf::Vector2f(100, 100), 100);
	Image map_image;
	map_image.loadFromFile("assets/G_v01.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
		//std::cout << time << std::endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Vector2f v(0, 0);
		v=player.sprite.getPosition();
		GetPlayerCoordinateForView(v.x, v.y);
		//interactionWithMap(v.x,v.y,dx,dy);
		//window.setView(view);
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == ' ') {
					s_map.setTextureRect(IntRect(0, 0, 90, 90));
				}
				if (TileMap[i][j] == 'b') {
					s_map.setTextureRect(IntRect(465, 0, 90, 90));
				}
				if ((TileMap[i][j] == '0')) {
					s_map.setTextureRect(IntRect(360, 0, 90, 90));
				}
				//s_map.scale(sf::Vector2f(0.112, 0.112));
				s_map.setPosition(j * 90, i * 90);
				window.draw(s_map);
			}
		}
		//window.draw(s_map);
		player.controle();
		float dx = player.speed.x;
		float dy = player.speed.y;
		v = player.sprite.getPosition();
		interactionWithMap(v.x, v.y, dx, dy);
		window.setView(view);

		player.textureRotate(pos);
		player.move(time);
		//window.clear();
		window.draw(player.sprite);
		window.display();
	}
	//system("pause");
	return EXIT_SUCCESS;

}