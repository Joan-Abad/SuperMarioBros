#include "MapCreationTool.h"
#include "GraphicUtilities.h"
#include "FontUtilities.h"
#include <iostream>


MapCreationTool::MapCreationTool(sf::RenderWindow & window, Map & map)
{
	//Mouse Position
	float margin_X = 64;
	float margin_y = 64;

	//Good
	mouseDetection.setSize(sf::Vector2f(4, 4));
	mouseDetection.setFillColor(sf::Color::Transparent);
	mouseDetection.setOrigin(mouseDetection.getSize().x / 2, mouseDetection.getSize().y / 2);


	//Map // Good
	mainMap = &map;

	//Tool Box // Good
	toolBoxSize = { 400,800 };
	toolBox.setSize(toolBoxSize);
	toolBox.setFillColor(sf::Color(220, 220, 220, 255));
	toolBox.setPosition(sf::Vector2f(window.getSize().x - toolBoxSize.x + 32, window.getSize().y / 8));
	numberOfEntitiessToolBox = 0;

	// Text // Good
	FontUtilities::InitializeText(text_Actors, font_Actors, "Font/MapCreation.otf");
	text_Actors.setString("Actors: ");
	text_Actors.setPosition(toolBox.getPosition().x + margin_X, toolBox.getPosition().y);
	text_Actors.setFillColor(sf::Color::Black);
	
	//New actors // Good
	CoinBlockP = new Entity;
	InitializeNewActor(CoinBlockP, "Art/Items/CoinBlock.png", sf::Vector2f(0,margin_y),e_CoinBlock);
	
	BrickBlockP = new Entity;
	InitializeNewActor(BrickBlockP,"Art/Items/Brick.png", sf::Vector2f(margin_X * 2,margin_y),e_Brick);

	FloorBlockP = new Entity;
	InitializeNewActor(FloorBlockP, "Art/Items/Floor.png", sf::Vector2f(0, margin_y * 3), e_Floor);

	PipeBlockP = new Entity;
	InitializeNewActor(PipeBlockP, "Art/Items/Pipe64.png", sf::Vector2f(margin_X * 2, margin_y * 3), e_Pipe);

	//Tools
	//Painting
	PaintTool = new Tool;
	InitializeNewTool(PaintTool, "Art/Items/Paint.png", sf::Vector2f(margin_X, toolBoxSize.y - margin_y * 1.2f), Painting);

	removeTool = new Tool;
	InitializeNewTool(removeTool, "Art/Items/Eraser.png", sf::Vector2f(margin_X * 2.5f, toolBoxSize.y - margin_y * 1.2f), Removing);

	//Good
	ToolMarker.setSize(sf::Vector2f(64, 64));
	ToolMarker.setFillColor(sf::Color::Transparent);
	ToolMarker.setPosition(PaintTool->spr_Entity.getPosition());

	//Good
	EntityMarker.setSize(sf::Vector2f(64, 64));
	EntityMarker.setFillColor(sf::Color::Transparent);

	//Good
	mouseMarker.setSize(sf::Vector2f(64, 64));
	mouseMarker.setOutlineThickness(2);
	mouseMarker.setPosition(300, 300);
	mouseMarker.setFillColor(sf::Color(255, 255, 255, 80));
	mouseMarker.setOutlineColor(sf::Color::Green);

	cameraMovementSpeed = 2;
	InitialCameraSpeed = cameraMovementSpeed;

	ActiveTool = new Tool;
}

//Initialize new actor, we should use this function for object player can interact with
void MapCreationTool::InitializeNewActor(Entity *entity, const std::string imageAddress, sf::Vector2f marginPosition, EntityType e_entType)
{
	//CoinBlock Actor Creation
	entity->imageAddress = imageAddress;
	GraphicUtilities::InitializeSprite(entity->spr_Entity, entity->tex_Entity, entity->imageAddress);
	entity->spr_Entity.setPosition(text_Actors.getPosition().x + marginPosition.x, text_Actors.getPosition().y + marginPosition.y);
	entity->E_EntityType = e_entType;
	AllEntitieP.push_back(entity);
}

//Initialize New Tool, need to update code as well at ToolsInput function
void MapCreationTool::InitializeNewTool(Tool *newTool, const std::string imageAddress, sf::Vector2f marginPosition, E_ToolMode toolMode)
{
	newTool->imageAddress = imageAddress;
	GraphicUtilities::InitializeSprite(newTool->spr_Entity, newTool->tex_Entity, newTool->imageAddress);
	newTool->spr_Entity.setPosition(text_Actors.getPosition().x + marginPosition.x, text_Actors.getPosition().y + marginPosition.y);
	newTool->toolType = toolMode;
	AllTools.push_back(newTool);
}

//Called when left button is pressed 
void MapCreationTool::CheckMouseInteraction(sf::RenderWindow &window, sf::View &view)
{
	sf::Vector2i PixelCords = sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
	mouseDetection.setPosition(sf::Vector2f(PixelCords));

	//Check If any tool is selected
	if (mouseDetection.getGlobalBounds().intersects(PaintTool->spr_Entity.getGlobalBounds()))
	{
		std::cout << "\nPaint selected";
		ActiveTool->toolType = Painting;
		ToolMarker.setFillColor(sf::Color(255, 255, 0, 80));
		ToolMarker.setPosition(PaintTool->spr_Entity.getPosition());
	}
	else if (mouseDetection.getGlobalBounds().intersects(removeTool->spr_Entity.getGlobalBounds()))
	{
		std::cout << "\nRemove Tool Selected";
		ActiveTool->toolType = Removing;
		EntityMarker.setFillColor(sf::Color::Transparent);
		ToolMarker.setFillColor(sf::Color(255, 255, 0, 80));
		ToolMarker.setPosition(removeTool->spr_Entity.getPosition());
		mouseMarker.setSize(sf::Vector2f(64, 64));
	}

	if (ActiveTool)
	{
		switch (ActiveTool->toolType)
		{
		case Painting:

			for (auto &entity : AllEntitieP)
			{
				if (mouseDetection.getGlobalBounds().intersects(entity->spr_Entity.getGlobalBounds()))
				{
					switch (entity->E_EntityType)
					{
					case e_CoinBlock:
						std::cout << "\nCoin Block";
						actorSpawned = new Actor("Art/Items/CoinBlock.png", e_CoinBlock);
						mouseMarker.setSize(sf::Vector2f(64, 64));
						break;

					case e_Brick:
						std::cout << "\nBrick Block";
						actorSpawned = new Actor("Art/Items/Brick.png", e_Brick);
						mouseMarker.setSize(sf::Vector2f(64, 64));
						break;

					case e_Floor:
						std::cout << "\nFloor Block";
						actorSpawned = new Actor("Art/Items/Floor.png", e_Floor);
						mouseMarker.setSize(sf::Vector2f(64, 64));
						break;
						
					case e_Pipe:
						std::cout << "\nPipe Block";
						actorSpawned = new Actor("Art/Items/Pipe128.png", e_Pipe);
						mouseMarker.setSize(sf::Vector2f(64*2, 64*2));
						break;
					}
					spawnActor = true;
					EntityMarker.setPosition(entity->spr_Entity.getPosition());
					EntityMarker.setFillColor(sf::Color(51, 204, 255, 180));
				}
				else
				{
					if (actorSpawned)
					{
						
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition,view);

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
				}
			}
			break;

		case Removing:

			actorSpawned = nullptr;

			for (int i = 0; i < mainMap->getAllActorsOnMap().size(); ++i)
			{
				if (mouseDetection.getGlobalBounds().intersects(mainMap->getAllActorsOnMap()[i]->getSprite().getGlobalBounds()))
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
		}
	}
}

void MapCreationTool::PaintActorIfPossible()
{
}

void MapCreationTool::UpdateCursorMarkerLocation(sf::RenderWindow &window)
{
	//If mouse marker is not above the toolbox
	if (!mouseMarker.getGlobalBounds().intersects(toolBox.getGlobalBounds()))
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, window.getView());
		mouseDetection.setPosition(sf::Vector2f(worldPos));

		worldPos.x = int(worldPos.x / 64);
		worldPos.y = int(worldPos.y / 64);
		worldPos.x *= 64;
		worldPos.y *= 64;

		mouseMarker.setPosition(worldPos);
		ShowCursorMarker();
	}
	//If mouse marker is above the toolbox
	else
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, window.getView());
		mouseDetection.setPosition(sf::Vector2f(worldPos));
		mouseMarker.setPosition(mouseDetection.getPosition());
		HideCursorMarker();
	}
	
}

void MapCreationTool::ShowCursorMarker()
{
	mouseMarker.setFillColor(sf::Color(255, 255, 255, 80));
	mouseMarker.setOutlineColor(sf::Color::Green);
}

void MapCreationTool::HideCursorMarker()
{
	mouseMarker.setFillColor(sf::Color::Transparent);
	mouseMarker.setOutlineColor(sf::Color::Transparent);
}

void MapCreationTool::MoveCamera(sf::View &view)
{
	std::cout << "\nMoving camera : " << cameraMovementSpeed;
	view.move(cameraMovementSpeed, 0);
	for (auto a : AllEntitieP)
	{
		a->spr_Entity.move(cameraMovementSpeed, 0);
	}
	toolBox.move(cameraMovementSpeed,0);
	text_Actors.move(cameraMovementSpeed, 0);
	for (auto tool : AllTools)
	{
		tool->spr_Entity.move(cameraMovementSpeed, 0);
	}

	EntityMarker.move(cameraMovementSpeed, 0);
	ToolMarker.move(cameraMovementSpeed, 0);
}

//Draw functionailty
void MapCreationTool::ShowMapCreationTool(sf::RenderWindow & window)
{
	window.draw(toolBox);
	window.draw(text_Actors);

	for (auto &tool : AllTools)
		window.draw(tool->spr_Entity);

	//Spawn Entities
	for (auto &entityP : AllEntitieP)
	{
		window.draw(entityP->spr_Entity);
	}

	window.draw(ToolMarker);
	window.draw(EntityMarker);
	window.draw(mouseMarker);
	window.draw(mouseDetection);
}

void MapCreationTool::HandleInputMapCreation(sf::RenderWindow &window, sf::View &view)
{
	sf::Event event;
	while (window.pollEvent(event))
	{

		switch (event.type)
		{
			//Close window
		case sf::Event::Closed:
			window.close();

			//If mouse button is pressed
		case sf::Event::MouseButtonPressed:
			
			switch (event.key.code)
			{
				//If mouse left button is pressed
			case sf::Mouse::Left: 
				LeftMouseButtonPressed = true;
				break;
			}
			break;
			
			//If Mouse Button is released
		case sf::Event::MouseButtonReleased:

			switch (event.key.code)
			{
				//If mouse left button is realeased
			case sf::Mouse::Left:
				LeftMouseButtonPressed = false;
				break;
			}
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code)
			{
			case sf::Keyboard::Q:
				moveCamera = true;
				cameraMovementSpeed = cameraStartMovementSpeed * -1;
				break;
			case sf::Keyboard::E:
				moveCamera = true;
				cameraMovementSpeed = cameraStartMovementSpeed;
				break;
			}
			break;

		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Q:
				moveCamera = false;
				break;
			case sf::Keyboard::E:
				moveCamera = false;
				break;
			}
		}

		
			//MoveCamera(view);

		UpdateCursorMarkerLocation(window);

	}
	if (LeftMouseButtonPressed == true)
		CheckMouseInteraction(window, view);

	if (moveCamera == true)
	{
		MoveCamera(view);
	}
}
