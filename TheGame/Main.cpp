#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"""
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	float CurrentFrame = 0;
	sf::Clock clock;
	Player player(sf::Vector2i(100, 100), 100);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 400;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.controle();
		player.move(time);
		window.clear();
		window.draw(player.sprite);
		window.display();
	}
	//system("pause");
	return EXIT_SUCCESS;
	
}