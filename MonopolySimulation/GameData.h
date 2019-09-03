#pragma once
#include <string>
#include <vector>
class GameData
{
	public:
		std::string ToJson();
		void AddPlayerPosition(int value);

	private:
		std::vector<int> playerPositions;
};

