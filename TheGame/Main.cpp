#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"""
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	float CurrentFrame = 0;
	sf::Clock clock;
	Player player(sf::Vector2f(100, 100), 100);

	while (window.isOpen())
	{
		float time = clock.restart().asMicroseconds();
		time = time / 600;

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
		player.move(time);
		window.clear();
		window.draw(player.sprite);
		window.display();
	}
	//system("pause");
	return EXIT_SUCCESS;
	
}