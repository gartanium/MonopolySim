#include "GameData.h"

std::string GameData::ToJson()
{
	std::string jsonObj = "PlayerPositions: [";
	for (int i = 0; i < playerPositions.size(); i++)
	{
		std::string position = std::to_string(playerPositions[i]);
		jsonObj += position + ", ";
	}

	jsonObj += "]";
	return jsonObj;
}

void GameData::AddPlayerPosition(int value)
{
	playerPositions.push_back(value);
}
