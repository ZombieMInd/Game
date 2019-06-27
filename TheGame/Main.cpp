#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"""
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	float CurrentFrame = 0;
	sf::Clock clock;
	Player player(sf::Vector2i(100, 100), 100);
	Player enemy(sf::Vector2i(100, 100), 100);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 400;

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.controle();
		player.textureRotate(pos);
		enemy.textureRotate(player.sprite.getPosition());
		player.move(time);
		window.clear();
		window.draw(player.sprite);
		window.draw(enemy.sprite);
		window.display();
	}
	//system("pause");
	return EXIT_SUCCESS;
	
}