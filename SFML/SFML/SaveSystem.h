#pragma once
#include <iostream>
#include <fstream>
#include "Actor.h"
#include "Map.h"

class Actor;
class Map;

class SaveSystem
{
public:
	SaveSystem();

private: 
	const std::string SaveFileName = "SaveFile.txt";

public: 
	void SaveActor(Actor &actorSpawned, int openFileMode);
	void LoadMap(Map &map);
	void SaveActorsTruncateFiles(std::vector<Actor*> actorVector);
};

