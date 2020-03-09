#include "MapCreationTool.h"
#include "GraphicUtilities.h"
#include "FontUtilities.h"
#include <iostream>

MapCreationTool::MapCreationTool(sf::RenderWindow & window)
{
	//Mouse Position
	float margin = 45;
	mouseDetection.setSize(sf::Vector2f(1,1));
	mouseDetection.setFillColor(sf::Color::Transparent);

	//Tool Box
	toolBoxSize = { 400,800 };
	toolBox.setSize(toolBoxSize);
	toolBox.setFillColor(sf::Color(220, 220, 220,255));
	toolBox.setPosition(sf::Vector2f(window.getSize().x - toolBoxSize.x,window.getSize().y/8));

	// Text
	FontUtilities::InitializeText(text_Actors,font_Actors,"Font/MapCreation.otf");
	text_Actors.setString("Actors: ");
	text_Actors.setPosition(toolBox.getPosition().x + margin, toolBox.getPosition().y);
	text_Actors.setFillColor(sf::Color::Black);

	//CoinBlock Actor Creation
	GraphicUtilities::InitializeSprite(CoinBlock.spr_Entity, CoinBlock.tex_Entity, "Art/Items/CoinBlock.png");
	CoinBlock.spr_Entity.setPosition(text_Actors.getPosition().x, text_Actors.getPosition().y + margin);

	//Push all Entities that can be spawn
	AllEntities.push_back(CoinBlock);

}

void MapCreationTool::ShowMapCreationTool(sf::RenderWindow & window)
{
	window.draw(toolBox);
	window.draw(text_Actors);

	//Draw all entities that we can spawn 
	for (auto entity : AllEntities)
		window.draw(entity.spr_Entity);
}

void MapCreationTool::HandleInput(sf::RenderWindow &window, Map & map)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (LeftMouseButtonPressed == false)
			{
				std::cout << "\nLeft mouse Button pressed.";
				LeftMouseButtonPressed = true;
			}
			
			//Update mouse very single time mouse moves
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			mouseDetection.setPosition(sf::Vector2f(mousePosition));

			//if mouse is on CoinBlock
			if (mouseDetection.getGlobalBounds().intersects(CoinBlock.spr_Entity.getGlobalBounds()) && actorSpawned == nullptr)
			{
				if (!actorSpawned)
				{
					std::cout << "\nNew actor spawned";
					actorSpawned = new Actor("Art/Items/CoinBlock.png");
					map.getAllActorsOnMap().push_back(actorSpawned);
				}				
			}

			if (actorSpawned)
			{
				sf::Vector2i getPositionToMoveActor; 
				getPositionToMoveActor.x = mousePosition.x / 64;
				getPositionToMoveActor.y = mousePosition.y / 64;
				std::cout << "\nX: " << getPositionToMoveActor.x;
				std::cout << "\nY: " << getPositionToMoveActor.y;

				getPositionToMoveActor.x *= 64;
				getPositionToMoveActor.y *= 64;
				
				actorSpawned->getSprite().setPosition(sf::Vector2f(getPositionToMoveActor));
			}
		}
		else 
		{
			if (LeftMouseButtonPressed == true)
			{
				LeftMouseButtonPressed = false; 
				std::cout << "\nLeft mouse Button released.";
				actorSpawned = nullptr; 
			}
			
			

			
		}
	}
}
