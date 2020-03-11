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
	MapCreationTool *mapCreationTool = nullptr;
	player.getSprite().setPosition(500,0);

	std::cout << "\nWant to open map Creation Tool (1 = YES | 2 = NO)?";
	std::cout << "\nAnswer: ";
	std::string answer;
	std::cin >> answer;
	if (answer == "1")
	 mapCreationTool = new MapCreationTool(window, map);
	

	std::ifstream ifs("SaveFile.txt");
	
	//Check if any file exists, if it does load the map
	if (ifs.is_open())
	{
		SaveSystem SS;
		SS.LoadMap(map);
	}
	
	//Set the window framerate to 60
	window.setFramerateLimit(60);

	//While game is running
	while (window.isOpen())
	{
		//Map creation Tool input
		if(mapCreationTool != nullptr)
		mapCreationTool->MapCreationInput(window);

		//Player functionalities
		player.PlayerMovement();
		player.CheckPlayerCollisions(map.getAllActorsOnMap());

		//Draw
		window.clear(sf::Color::White);

		if(mapCreationTool)
		mapCreationTool->ShowMapCreationTool(window);

		map.DrawAllActors(window);
		player.DrawPlayer(window);
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}