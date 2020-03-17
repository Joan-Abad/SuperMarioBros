#include "SaveSystem.h"
#include <string>
#include <iostream>
#include <vector>

SaveSystem::SaveSystem() = default;


void SaveSystem::SaveActor(Actor &actorSpawned,  int openFileMode)
{
	auto a = std::ofstream::app;
	std::ofstream SaveFile;
	SaveFile.open(SaveFileName, openFileMode);
	
	if (actorSpawned.actorType == e_CoinBlock)
	{
		SaveFile << "CoinBlock,";
	}
	else if (actorSpawned.actorType == e_Brick)
	{
		SaveFile << "Brick,";
	}
	else if (actorSpawned.actorType == e_Floor)
	{
		SaveFile << "Floor,";
	}
	else if (actorSpawned.actorType == e_Pipe)
	{
		SaveFile << "Pipe,";
	}

	SaveFile << actorSpawned.getSprite().getPosition().x << "," << actorSpawned.getSprite().getPosition().y << ';' << std::endl;

	SaveFile.close();

}

void SaveSystem::SaveActorsTruncateFiles(std::vector<Actor*> actorVector)
{
	auto a = std::ofstream::app;
	std::ofstream SaveFile;
	SaveFile.open(SaveFileName, std::ofstream::trunc);

	for (auto actor : actorVector)
	{
		if (actor->actorType == e_CoinBlock)
		{
			SaveFile << "CoinBlock,";
		}
		else if (actor->actorType == e_Brick)
		{
			SaveFile << "Brick,";
		}
		else if (actor->actorType == e_Floor)
		{
			SaveFile << "Floor,";
		}
		else if (actor->actorType == e_Pipe)
		{
			SaveFile << "Pipe,";
		}
		SaveFile << actor->getSprite().getPosition().x << "," << actor->getSprite().getPosition().y << ';' << std::endl;

	}

}


void SaveSystem::LoadMap(Map &map)
{
	std::ifstream myfile(SaveFileName);
	
	std::vector<std::string> SaveFileInfo;

	std::string line;

	//Read and Store all Lines of the document
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			SaveFileInfo.push_back(line);
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";

	std::string word1;
	std::vector<std::string> wordsFound;
	int item = 0;

	//Read all characters and store the data
	for(int i = 0; i < SaveFileInfo.size(); i++)
	{
			for (auto j = 0; j < SaveFileInfo[i].size(); j++)
			{
				if (SaveFileInfo[i][j] != ',' && SaveFileInfo[i][j] != ';')
				{
					word1 += SaveFileInfo[i][j];
				}
				else
				{
					item++;
					wordsFound.push_back(word1);
					word1.clear();
				}

			}
	}
	
	int arrayHandler = 0;
	std::string s_ItemType;
	sf::Vector2f PositionSaveFile;
	std::string imageAddress;
	EntityType enty;
	for (int i = 0; i < wordsFound.size(); i++)
	{
		if (arrayHandler == 0)
		{
			s_ItemType = wordsFound[i];
		}
		else if (arrayHandler == 1)
		{
			PositionSaveFile.x = std::stof(wordsFound[i]);
		}
		else if (arrayHandler == 2)
		{
			PositionSaveFile.y = std::stof(wordsFound[i]); 
			if (s_ItemType == "CoinBlock")
			{
				imageAddress = "Art/Items/CoinBlock.png";
				enty = e_CoinBlock;
			}
			else if (s_ItemType == "Brick")
			{
				imageAddress = "Art/Items/Brick.png";
				enty = e_Brick;
			}
			else if (s_ItemType == "Floor")
			{
				imageAddress = "Art/Items/Floor.png";
				enty = e_Floor;
			}
			else if (s_ItemType == "Pipe")
			{
				imageAddress = "Art/Items/Pipe128.png";
				enty = e_Pipe;
			}
			Actor *actorSpawned = new Actor(imageAddress, enty);
			actorSpawned->getSprite().setPosition(PositionSaveFile);
			map.getAllActorsOnMap().push_back(actorSpawned);
			arrayHandler = -1;
		}
		arrayHandler++;
	}	
}

