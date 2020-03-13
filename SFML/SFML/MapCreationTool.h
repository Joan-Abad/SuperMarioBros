#pragma once
#include "SFML/Graphics.hpp"
#include "Actor.h"
#include <vector>
#include "Map.h"
#include "SaveSystem.h"

extern enum EntityType
{
	e_CoinBlock,
	e_Brick,
	NONE
};

enum E_ToolMode
{
	Painting,
	Removing, 
	e_NONE
};

struct Entity
{
	sf::Sprite spr_Entity;
	sf::Texture tex_Entity;
	EntityType E_EntityType;
	std::string imageAddress;
};

struct Tool
{
	sf::Sprite spr_Entity;
	sf::Texture tex_Entity;
	E_ToolMode toolType;
	std::string imageAddress;
};

class Actor;
class Map;

class MapCreationTool
{

public: 
	MapCreationTool(sf::RenderWindow & window, Map & map);
	Map * mainMap;

private: 

	//Mouse (Red Square)
	sf::RectangleShape mouseDetection; 
	
	int numberOfEntitiessToolBox;

	//Initializes new actor available in sandbox toolbox
	void InitializeNewActor(Entity &entity, const std::string imageAddress, sf::Vector2f marginPosition, EntityType e_entType);
	void InitializeNewTool(Tool &newTool, const std::string imageAddress, sf::Vector2f marginPosition, E_ToolMode toolMode);

	void DeleteActor(Entity &entity);

	bool HoldingLeftButton = false; 
	bool moveCamera = false;

	float InitialCameraSpeed;
	float cameraMovementSpeed; 
	float movementAdded;
	float ajustarMouseMarker;

	float XAXA;
//Tool Box
	//Graphics
	sf::RectangleShape toolBox;
	sf::Vector2f toolBoxSize; 
	
	//Letters
	sf::Text text_Actors;
	sf::Font font_Actors;
	
	//Entities in toolbox
	Entity CoinBlock; 
	Entity Brick;
	Entity * CoinBlockP = nullptr;
	Entity * BrickBlockP = nullptr;

	//Tools
	Tool paintTool;
	Tool removeTool;
	Tool *ActiveTool = nullptr;

	//Markers
	sf::RectangleShape RectangleMarker;
	sf::RectangleShape EntityMarker;
	sf::RectangleShape mouseMarker;

	//Actors
	Actor * actorSpawned = nullptr;
	bool spawnActor = true;

	// Vectors 
	std::vector<Entity> AllEntities;
	std::vector<Tool> AllTools;
	std::vector<Entity*> AllEntitieP;

	bool LeftMouseButtonPressed = false; 

	//All the input tools can make
	void ToolsInput(sf::RenderWindow &window);
public: 
	//Draw all the map creaction tool
	void ShowMapCreationTool(sf::RenderWindow &window);
	
	//Map creation input
	void MapCreationInput(sf::RenderWindow &window, sf::View &view);

	void updateMouseMaker(sf::Vector2i mousePosition);

	void moveToolBox(float speed);

	Entity &getCoinblock() { return CoinBlock; };
	Entity &getBrickBlock() { return Brick; };
};

