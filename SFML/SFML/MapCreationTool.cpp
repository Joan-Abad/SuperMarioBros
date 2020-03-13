#include "MapCreationTool.h"
#include "GraphicUtilities.h"
#include "FontUtilities.h"
#include <iostream>


MapCreationTool::MapCreationTool(sf::RenderWindow & window, Map & map) 
{
	//Mouse Position
	float margin_X = 64;
	float margin_y = 64;

	mouseDetection.setSize(sf::Vector2f(4,4));
	mouseDetection.setFillColor(sf::Color::Transparent);
	mouseDetection.setOrigin(mouseDetection.getSize().x / 2, mouseDetection.getSize().y / 2);
	

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

	
	//Brick Actor Creation	
	InitializeNewActor(Brick, "Art/Items/Brick.png", sf::Vector2f(Brick.tex_Entity.getSize().x + margin_X *2, margin_y), e_Brick);
	
	//CoinBlock Actor Creation
	InitializeNewActor(CoinBlock, "Art/Items/CoinBlock.png", sf::Vector2f(0, margin_y), e_CoinBlock);



	CoinBlockP = new Entity;
	CoinBlockP->E_EntityType = e_CoinBlock;
	GraphicUtilities::InitializeSprite(CoinBlockP->spr_Entity,CoinBlockP->tex_Entity,"Art/Items/CoinBlock.png");
	CoinBlockP->spr_Entity.setPosition(text_Actors.getPosition().x, text_Actors.getPosition().y + margin_y);
	AllEntitieP.push_back(CoinBlockP);

	BrickBlockP = new Entity;
	BrickBlockP->E_EntityType = e_Brick;
	GraphicUtilities::InitializeSprite(BrickBlockP->spr_Entity, BrickBlockP->tex_Entity, "Art/Items/Brick.png");
	BrickBlockP->spr_Entity.setPosition(text_Actors.getPosition().x + Brick.tex_Entity.getSize().x + margin_X * 2, text_Actors.getPosition().y + margin_y);
	AllEntitieP.push_back(BrickBlockP);

//Tools
	//Painting
	InitializeNewTool(paintTool, "Art/Items/Paint.png", sf::Vector2f(margin_X, toolBoxSize.y - margin_y * 1.2f), Painting);
	InitializeNewTool(removeTool, "Art/Items/Eraser.png", sf::Vector2f(margin_X * 2.5f, toolBoxSize.y - margin_y * 1.2f), Removing);

	RectangleMarker.setSize(sf::Vector2f(64, 64));
	RectangleMarker.setFillColor(sf::Color::Transparent);
	RectangleMarker.setPosition(paintTool.spr_Entity.getPosition());

	EntityMarker.setSize(sf::Vector2f(64, 64));
	EntityMarker.setFillColor(sf::Color::Transparent);

	mouseMarker.setSize(sf::Vector2f(64,64));
	mouseMarker.setOutlineThickness(2);
	mouseMarker.setPosition(300,300);
	mouseMarker.setFillColor(sf::Color(255,255,255,80));
	mouseMarker.setOutlineColor(sf::Color::Green);

	cameraMovementSpeed = 2;
	InitialCameraSpeed = cameraMovementSpeed;
}

//Initialize new actor, we should use this function for object player can interact with
void MapCreationTool::InitializeNewActor(Entity &entity, const std::string imageAddress, sf::Vector2f marginPosition, EntityType e_entType)
{
	//CoinBlock Actor Creation
	entity.imageAddress = imageAddress;
	//GraphicUtilities::InitializeSprite(entity.spr_Entity, entity.tex_Entity, entity.imageAddress);
	//entity.spr_Entity.setPosition(text_Actors.getPosition().x + marginPosition.x, text_Actors.getPosition().y + marginPosition.y);
	
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
void MapCreationTool::MapCreationInput(sf::RenderWindow &window, sf::View &view)
{
	sf::Event event;
	while (window.pollEvent(event))
	{

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

		mouseDetection.setPosition(worldPos.x, worldPos.y);

		
		//set position from the actor spawned to the "64" graph
		worldPos.x = int(worldPos.x / 64);
		worldPos.y = int(worldPos.y / 64);
		worldPos.x *= 64;
		worldPos.y *= 64;
		//mousePosition.x += ajustarMouseMarker / 64;
		
		mouseMarker.setPosition(worldPos.x, worldPos.y);

		//RectangleMarker.setPosition(sf::Vector2f(mousePosition));
		//mouseDetection.setOrigin();
		


		//if mouse is above toolbox
		if (mouseDetection.getGlobalBounds().intersects(toolBox.getGlobalBounds()) || mouseMarker.getGlobalBounds().intersects(toolBox.getGlobalBounds()))
		{
			mouseMarker.setFillColor(sf::Color::Transparent);
			mouseMarker.setOutlineColor(sf::Color::Transparent);
		}
		else
		{
			mouseMarker.setFillColor(sf::Color(255, 255, 255, 80));
			mouseMarker.setOutlineColor(sf::Color::Green);
		}

		//If window is closed
		if (event.type == sf::Event::Closed)
			window.close();

		//LEFT MOUSE BUTTON
		if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			HoldingLeftButton = true;
		else if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			HoldingLeftButton = false;

		//Key Pressed
		if (event.type == sf::Event::KeyPressed)
		{
				//Camera Movement (Q and E)
			if (event.key.code == sf::Keyboard::Q)
			{
				moveCamera = true;
				cameraMovementSpeed = InitialCameraSpeed * -1;			
				movementAdded += cameraMovementSpeed;
			}
			else if (event.key.code == sf::Keyboard::E)
			{
				moveCamera = true;
				cameraMovementSpeed = InitialCameraSpeed;
				movementAdded += cameraMovementSpeed;
			}
		}
		//Key Released
		if (event.type == sf::Event::KeyReleased)
		{
			//Camera Movement (Q and E)
			if (event.key.code == sf::Keyboard::Q)
			{
				moveCamera = false;
			}
			else if (event.key.code == sf::Keyboard::E)
			{
				moveCamera = false;
			}
		}
	


		if (HoldingLeftButton)
			ToolsInput(window);

		if (moveCamera)
		{
			moveToolBox(cameraMovementSpeed);
			view.move(cameraMovementSpeed, 0);
		}


		
		
	}
}

void MapCreationTool::updateMouseMaker(sf::Vector2i mousePosition)
{
	
}

void MapCreationTool::moveToolBox(float speed)
{
	toolBox.move(speed, 0);
	text_Actors.move(speed, 0);
	
	for (int i = 0; i < AllEntities.size(); i++)
	{
		AllEntities[i].spr_Entity.move(speed, 0);
	}

	for (auto &EntityP : AllEntitieP)
	{
		EntityP->spr_Entity.move(speed, 0);
	}

	for (auto &Tool : AllTools)
	{
		Tool.spr_Entity.move(speed,0);
	}
	RectangleMarker.move(speed, 0);
	//EntityMarker.move(speed, 0);

	
}

void MapCreationTool::ToolsInput(sf::RenderWindow &window)
{
	LeftMouseButtonPressed = true;
	//Update mouse very single time mouse moves
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	//set position from the actor spawned to the "64" graph
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

	mouseDetection.setPosition(worldPos.x, worldPos.y);


	//set position from the actor spawned to the "64" graph
	worldPos.x = int(worldPos.x / 64);
	worldPos.y = int(worldPos.y / 64);
	worldPos.x *= 64;
	worldPos.y *= 64;


	//mouseMarker.setPosition(worldPos.x, worldPos.y);
	
	mouseDetection.setPosition(sf::Vector2f(mousePosition));

	
	//If paint entity gets pressed
	if (mouseDetection.getGlobalBounds().intersects(paintTool.spr_Entity.getGlobalBounds()))
	{
		RectangleMarker.setPosition(paintTool.spr_Entity.getPosition().x + (movementAdded * -1), paintTool.spr_Entity.getPosition().y);
		RectangleMarker.setFillColor(sf::Color(255, 0, 0, 122));
		ActiveTool = &paintTool;
		std::cout << "\nPaint getting pressed";
		//EntityMarker.setFillColor(sf::Color(sf::Color(0, 255, 255, 122)));
	}

	//If removing entity get's pressed 
	else if (mouseDetection.getGlobalBounds().intersects(removeTool.spr_Entity.getGlobalBounds()))
	{
		RectangleMarker.setPosition(removeTool.spr_Entity.getPosition().x + 4, removeTool.spr_Entity.getPosition().y);
		RectangleMarker.setFillColor(sf::Color(255, 0, 0, 122));
		EntityMarker.setFillColor(sf::Color::Transparent);
		ActiveTool = &removeTool;
		std::cout << "\nRemove getting pressed";

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
						std::cout << "\nStore Coin Block";

					}

					//Check if its a brick block
					else if (entity.E_EntityType == e_Brick)
					{
						std::cout << "\nNew actor Stored";
						actorSpawned = new Actor("Art/Items/Brick.png", e_Brick);
						std::cout << "\nStore Brick Block";
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
						sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

						mouseDetection.setPosition(worldPos.x, worldPos.y);


						//set position from the actor spawned to the "64" graph
						worldPos.x = int(worldPos.x / 64);
						worldPos.y = int(worldPos.y / 64);
						worldPos.x *= 64;
						worldPos.y *= 64;
						//mousePosition.x += ajustarMouseMarker / 64;

						mouseMarker.setPosition(worldPos.x, worldPos.y);
						actorSpawned->getSprite().setPosition(sf::Vector2f(worldPos));

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

						for (auto entity : AllEntities)
						{
							if (entity.spr_Entity.getGlobalBounds().intersects(actorSpawned->getSprite().getGlobalBounds()))
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
						if (actorSpawn == true && LeftMouseButtonPressed == true)
						{
							SaveSystem SS;
							Actor *actor = new Actor(*actorSpawned);
							mainMap->getAllActorsOnMap().push_back(actor);
							std::cout << "\nNew actor spawned.";
							std::cout << "\nNumber of actors spawned in the map: " << mainMap->getAllActorsOnMap().size();
							SS.SaveActor(*actor, std::ofstream::app);
						}
					}
					else
					{
						//set position from the actor spawned to the "64" graph
						sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

						mouseDetection.setPosition(worldPos.x, worldPos.y);


						//set position from the actor spawned to the "64" graph
						worldPos.x = int(worldPos.x / 64);
						worldPos.y = int(worldPos.y / 64);
						worldPos.x *= 64;
						worldPos.y *= 64;
						//mousePosition.x += ajustarMouseMarker / 64;

						mouseMarker.setPosition(worldPos.x, worldPos.y);
					}
				}
			}

			for (auto entityP : AllEntitieP)
			{
				if (mouseDetection.getGlobalBounds().intersects(entityP->spr_Entity.getGlobalBounds()))
				{
					switch (entityP->E_EntityType)
					{
					case e_CoinBlock:
						std::cout << "\nCoinBlock detected";
						std::cout << "\nNew actor Stored";
						actorSpawned = new Actor("Art/Items/CoinBlock.png", e_CoinBlock);
						std::cout << "\nStore Coin Block";
						break;
					case e_Brick:
						std::cout << "\nBrickBlock detected";
						std::cout << "\nNew actor Stored";
						actorSpawned = new Actor("Art/Items/Brick.png", e_Brick);
						std::cout << "\nStore Brick Block";
						break;
					}
				}

				
			}
			break;
			//Chec if tool is removing tool
		case Removing:
			//Check all actors on the map if they are interacting with our mouse, if they do delete the object and remove in from the vector
			//Save the new file as well.
			actorSpawned = nullptr;

			//set position from the actor spawned to the "64" graph
			{
				sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

				mouseDetection.setPosition(worldPos.x, worldPos.y);


				//set position from the actor spawned to the "64" graph
				worldPos.x = int(worldPos.x / 64);
				worldPos.y = int(worldPos.y / 64);
				worldPos.x *= 64;
				worldPos.y *= 64;
				//mousePosition.x += ajustarMouseMarker / 64;

				mouseMarker.setPosition(worldPos.x, worldPos.y);
			}

			for (int i = 0; i < mainMap->getAllActorsOnMap().size(); i++)
			{
				if (mainMap->getAllActorsOnMap()[i]->getSprite().getGlobalBounds().intersects(mouseDetection.getGlobalBounds()))
				{	
					delete(mainMap->getAllActorsOnMap()[i]);
					mainMap->getAllActorsOnMap().erase(mainMap->getAllActorsOnMap().begin() + i);
					i--;
					SaveSystem SS;
					SS.SaveActorsTruncateFiles(mainMap->getAllActorsOnMap());
					std::cout << "\nActor removed.";
					std::cout << "\nNumber of actors spawned in the map: " << mainMap->getAllActorsOnMap().size();
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
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

		mouseDetection.setPosition(worldPos.x, worldPos.y);


		//set position from the actor spawned to the "64" graph
		worldPos.x = int(worldPos.x / 64);
		worldPos.y = int(worldPos.y / 64);
		worldPos.x *= 64;
		worldPos.y *= 64;
		//mousePosition.x += ajustarMouseMarker / 64;
		mouseMarker.setPosition(worldPos.x, worldPos.y);
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

	for (auto &entityP : AllEntitieP)
	{
		window.draw(entityP->spr_Entity);
	}

	window.draw(RectangleMarker);
	window.draw(EntityMarker);
	window.draw(mouseMarker);
	window.draw(mouseDetection);
}
