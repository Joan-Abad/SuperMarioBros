#include <SFML/Graphics.hpp>
#include "SaveSystem.h"
#include "Actor.h"
#include "MapCreationTool.h"
#include <iostream>
#include "Player.h"
#include "MapCreationTool.h"
#include <fstream>

Player player("Art/Character/Mario1.png");


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mario Bros");
	Map map;
	MapCreationTool *mapCreationTool = new MapCreationTool(window, map);
	player.getSprite().setPosition(500,0);

	/*std::cout << "\nWant to open map Creation Tool (1 = YES | 2 = NO)?";
	std::cout << "\nAnswer: ";
	std::string answer;
	std::cin >> answer;
	if (answer == "1")
	 mapCreationTool = new MapCreationTool(window, map);*/ 
	

	std::ifstream ifs("SaveFile.txt");
	
	//Check if any file exists, if it does load the map
	if (ifs.is_open())
	{
		SaveSystem SS;
		SS.LoadMap(map);
	}
	sf::View view(sf::Vector2f(window.getSize().x/2, window.getSize().y / 2), sf::Vector2f(window.getSize()));

	//Set the window framerate to 60
	window.setFramerateLimit(60);

	//window.setView(view);

	if (mapCreationTool)
	{

		//While game is running
		while (window.isOpen())
		{
			//Player functionalities
			player.PlayerMovement();
			player.CheckPlayerCollisions(map.getAllActorsOnMap());


			mapCreationTool->HandleInputMapCreation(window,view);

			//Draw
			window.clear(sf::Color(89, 150, 255));
			map.DrawAllActors(window);

			if (mapCreationTool)
				mapCreationTool->ShowMapCreationTool(window);

			window.setView(view);

			player.DrawPlayer(window);
			window.draw(player.getSprite());
			window.display();
			
		}
	}

	return 0;
}