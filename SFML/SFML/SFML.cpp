#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "MapCreationTool.h"
#include <iostream>

Actor actor1("Art/Items/CoinBlock.png");
Actor actor2("Art/Items/CoinBlock.png");

int main()
{
	actor1.getSprite().setColor(sf::Color::Green);
	actor1.getSprite().setPosition(64*7,64*5);
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mario Bros");
	MapCreationTool mapCreationTool(window);
	Map mapOnCT;

	
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		mapCreationTool.HandleInput(window, mapOnCT);

		window.clear(sf::Color::White);
		mapCreationTool.ShowMapCreationTool(window);
		mapOnCT.DrawAllActors(window);
		window.draw(actor1.getSprite());

		for (auto box : mapOnCT.getAllActorsOnMap())
		{
			if (box->CheckActorCollision(actor1))
			{
				std::cout << "\nColliding";
			}
		}
		window.display();
	}

	return 0;
}