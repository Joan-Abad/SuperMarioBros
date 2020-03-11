#include "MapCreationTool.h"
#include "GraphicUtilities.h"
#include "FontUtilities.h"
#include <iostream>


MapCreationTool::MapCreationTool(sf::RenderWindow & window, Map & map) 
{
	//Mouse Position
	float margin_X = 64;
	float margin_y = 64;
	mouseDetection.setSize(sf::Vector2f(1,1));
	mouseDetection.setFillColor(sf::Color::Transparent);
	

	//Map
	mainMap = &map;

	//Tool Box
	toolBoxSize = { 400,800 };
	toolBox.setSize(toolBoxSize);
	toolBox.setFillColor(sf::Color(220, 220, 220,255));
	toolBox.setPosition(sf::Vector2f(window.getSize().x - toolBoxSize.x,window.getSize().y/8));
	numberOfEntitiessToolBox = 0;

	// Text
	FontUtilities::InitializeText(text_Actors,font_Actors,"Font/MapCreation.otf");
	text_Actors.setString("Actors: ");
	text_Actors.setPosition(toolBox.getPosition().x + margin_X, toolBox.getPosition().y);
	text_Actors.setFillColor(sf::Color::Black);

//ENTITIES


	//CoinBlock Actor Creation
	InitializeNewActor(CoinBlock, "Art/Items/CoinBlock.png",sf::Vector2f(0,margin_y),e_CoinBlock);

	//Brick Actor Creation	
	InitializeNewActor(Brick, "Art/Items/Brick.png", sf::Vector2f(Brick.tex_Entity.getSize().x + margin_X *2, margin_y), e_Brick);
	
//Tools
	//Painting
	InitializeNewTool(paintTool, "Art/Items/Paint.png", sf::Vector2f(margin_X, toolBoxSize.y - margin_y * 1.2f), Painting);
	InitializeNewTool(removeTool, "Art/Items/Eraser.png", sf::Vector2f(margin_X * 2.5f, toolBoxSize.y - margin_y * 1.2f), Removing);

	RectangleMarker.setSize(sf::Vector2f(64, 64));
	RectangleMarker.setFillColor(sf::Color::Transparent);
	RectangleMarker.setPosition(paintTool.spr_Entity.getPosition());

	EntityMarker.setSize(sf::Vector2f(64, 64));
	EntityMarker.setFillColor(sf::Color::Transparent);
}

//Initialize new actor, we should use this function for object player can interact with
void MapCreationTool::InitializeNewActor(Entity &entity, const std::string imageAddress, sf::Vector2f marginPosition, EntityType e_entType)
{
	//CoinBlock Actor Creation
	entity.imageAddress = imageAddress;
	GraphicUtilities::InitializeSprite(entity.spr_Entity, entity.tex_Entity, entity.imageAddress);
	entity.spr_Entity.setPosition(text_Actors.getPosition().x + marginPosition.x, text_Actors.getPosition().y + marginPosition.y);
	entity.E_EntityType = e_entType;
	AllEntities.push_back(entity);
}

//Initialize New Tool, need to update code as well at ToolsInput function
void MapCreationTool::InitializeNewTool(Tool &newTool, const std::string imageAddress, sf::Vector2f marginPosition, E_ToolMode toolMode)
{
	newTool.imageAddress = imageAddress;
	GraphicUtilities::InitializeSprite(newTool.spr_Entity,newTool.tex_Entity,newTool.imageAddress);
	newTool.spr_Entity.setPosition(text_Actors.getPosition().x + marginPosition.x, text_Actors.getPosition().y + marginPosition.y);
	newTool.toolType = toolMode;
	AllTools.push_back(newTool);
}


void MapCreationTool::DeleteActor(Entity &entity)
{
	if (mouseDetection.getGlobalBounds().intersects(entity.spr_Entity.getGlobalBounds()) && actorSpawned == nullptr)
	{
		std::cout << "Deleting entity";
	}
}

//Main function, called in sfml.cpp
void MapCreationTool::MapCreationInput(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		//If window is closed
		if (event.type == sf::Event::Closed)
			window.close();

		//If Left mouse button is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Check if tools are being used
			ToolsInput(window);

			//Keep adding input...
		}
	}
}

void MapCreationTool::ToolsInput(sf::RenderWindow &window)
{
	LeftMouseButtonPressed = true;
	//Update mouse very single time mouse moves
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	mouseDetection.setPosition(sf::Vector2f(mousePosition));

	//If paint entity gets pressed
	if (mouseDetection.getGlobalBounds().intersects(paintTool.spr_Entity.getGlobalBounds()))
	{
		RectangleMarker.setPosition(paintTool.spr_Entity.getPosition());
		RectangleMarker.setFillColor(sf::Color(255, 0, 0, 122));
		ActiveTool = &paintTool;
		//EntityMarker.setFillColor(sf::Color(sf::Color(0, 255, 255, 122)));
	}

	//If removing entity get's pressed 
	else if (mouseDetection.getGlobalBounds().intersects(removeTool.spr_Entity.getGlobalBounds()))
	{
		RectangleMarker.setPosition(removeTool.spr_Entity.getPosition());
		RectangleMarker.setFillColor(sf::Color(255, 0, 0, 122));
		EntityMarker.setFillColor(sf::Color::Transparent);
		ActiveTool = &removeTool;
	}

	//If any tool is selected
	if (ActiveTool)
	{
		//Check which tool it is 
		switch (ActiveTool->toolType)
		{
			//Chec if tool is painting tool
		case Painting:
			//Go through all entities
			for (auto entity : AllEntities)
			{
				//If mouse is intersecting with any entity sprite
				if (mouseDetection.getGlobalBounds().intersects(entity.spr_Entity.getGlobalBounds()))
				{
					//Check if its a coin block
					if (entity.E_EntityType == e_CoinBlock)
					{
						std::cout << "\nNew actor Stored";
						actorSpawned = new Actor("Art/Items/CoinBlock.png", e_CoinBlock);
					}

					//Check if its a brick block
					else if (entity.E_EntityType == e_Brick)
					{
						std::cout << "\nNew actor Stored";
						actorSpawned = new Actor("Art/Items/Brick.png", e_Brick);
					}
					//Move and color the marker depending what entity is selected.
					EntityMarker.setPosition(entity.spr_Entity.getPosition());
					EntityMarker.setFillColor(sf::Color(0, 255, 255, 122));
				}
				//If mouse is not interacting with any entity
				else
				{
					//Check is left mouse button is being pressed and actor spawned has any value
					if (actorSpawned && LeftMouseButtonPressed == true)
					{
						//set position from the actor spawned to the "64" graph
						sf::Vector2i getPositionToMoveActor;
						getPositionToMoveActor.x = mousePosition.x / 64;
						getPositionToMoveActor.y = mousePosition.y / 64;
						getPositionToMoveActor.x *= 64;
						getPositionToMoveActor.y *= 64;
						actorSpawned->getSprite().setPosition(sf::Vector2f(getPositionToMoveActor));

						//boolean to control the spawn from the actor. 
						bool actorSpawn = true;

						//We will check if there is no object in that position for spawning the new acto

						// We check all actors of the map
						for (auto actor : mainMap->getAllActorsOnMap())
						{
							if (actor->getSprite().getPosition() == actorSpawned->getSprite().getPosition())
							{
								actorSpawn = false;
							}
						}

						//We check that we don't attempt to interact with the toolbox
						if (toolBox.getGlobalBounds().intersects(actorSpawned->getSprite().getGlobalBounds()))
						{
							actorSpawn = false;
						}

						//Spawn the actor, push it to actors vector on Map object and save this file.
						if (actorSpawn == true)
						{
							SaveSystem SS;
							Actor *actor = new Actor(*actorSpawned);
							mainMap->getAllActorsOnMap().push_back(actor);
							std::cout << "\New actor spawned.";
							std::cout << "\nNumber of actors spawned in the map: " << mainMap->getAllActorsOnMap().size();
							SS.SaveActor(*actor, std::ofstream::app);
						}
					}
				}
			}
			break;
			//Chec if tool is removing tool
		case Removing:
			//Check all actors on the map if they are interacting with our mouse, if they do delete the object and remove in from the vector
			//Save the new file as well.
			for (int i = 0; i < mainMap->getAllActorsOnMap().size(); i++)
			{
				if (mainMap->getAllActorsOnMap()[i]->getSprite().getGlobalBounds().intersects(mouseDetection.getGlobalBounds()))
				{
					delete(mainMap->getAllActorsOnMap()[i]);
					mainMap->getAllActorsOnMap().erase(mainMap->getAllActorsOnMap().begin() + i);
					i--;
					SaveSystem SS;
					SS.SaveActorsTruncateFiles(mainMap->getAllActorsOnMap());
				}
			}
			break;
		//Notice if there is no tool type selected.
		case e_NONE:
			std::cerr << "\nError: No tool type selected";
			break;
		}


	}
	//If left mouse button is not being pressed, mark it as false. 
	else
	{
		LeftMouseButtonPressed = false;
	}

}

//Draw functionailty
void MapCreationTool::ShowMapCreationTool(sf::RenderWindow & window)
{
	window.draw(toolBox);
	window.draw(text_Actors);

	//Draw all entities that we can spawn 
	for (auto entity : AllEntities)
		window.draw(entity.spr_Entity);

	for (auto tool : AllTools)
		window.draw(tool.spr_Entity);

	window.draw(RectangleMarker);
	window.draw(EntityMarker);
}
