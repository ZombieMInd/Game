#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "map.h"
#include "view.h"
using namespace sf;
// размер персонажа
const float h = 5;
const float w = 5;

void interactionWithMap(float x, float y, float dx, float dy){
	Player player1(sf::Vector2f(150, 150), 100);//ф-ция взаимодействия с картой
	for (int i = y / 90; i < (y + h) / 90; i++) {//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
		for (int j = x / 90; j < (x + w) / 90; j++){//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			if (TileMap[i][j] == '0'){//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
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
			if (TileMap[i][j] == 'b') { //если символ равен 's' (камень)

				TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
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