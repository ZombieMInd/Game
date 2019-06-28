#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "map.h"
#include "view.h"
using namespace sf;
// размер персонажа
const float h = 40;
const float w = 40;
const int blcsize = 90;
void interactionWithMap(Player& pp,float x, float y, float dx, float dy) {
	//ф-ция взаимодействия с картой
	/*float dx = pp.speed.x;
	float dy = pp.speed.y;
	sf::Vector2f v = pp.sprite.getPosition();
	float x = v.x,startx=x;
	float y = v.y,starty=y;*/
	float startx = x;
	float starty = y;
	for (int i = y / blcsize; i < (y + h) / blcsize; i++) {
		for (int j = x / blcsize; j < (x + w) / blcsize; j++){
			if (TileMap[i][j] == '0'){
				if (dy > 0){
					y = i * blcsize - h;
					pp.setPosition(startx, y);
				}
				if (dy < 0){
					y = i * blcsize + blcsize;
					pp.setPosition(startx, y);
				}
				if (dx > 0){
					x = j * blcsize - w;
					pp.setPosition(x, starty);
				}
				if (dx < 0){
					x = j * blcsize + blcsize;
					pp.setPosition(x, starty);
				}
				//pp.setPosition(x, y);
			}
			//pp.setPosition(x, y);
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
	Player player(sf::Vector2f(150, 150), 100);
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
					s_map.setTextureRect(IntRect(360, 0, 90, 90));
				}
				if (TileMap[i][j] == 'b') {
					s_map.setTextureRect(IntRect(465, 0, 90, 90));
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
		player.controle();
		float dx = player.speed.x;
		float dy = player.speed.y;
		v = player.sprite.getPosition();
		player.move(time);
		interactionWithMap(player,v.x,v.y,dx,dy);
		window.setView(view);

		player.textureRotate(pos);
		window.draw(player.sprite);
		window.display();
	}
	//system("pause");
	return EXIT_SUCCESS;

}