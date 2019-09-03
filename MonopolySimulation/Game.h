#pragma once
#include "DiceHandler.h"
#include <vector>
#include "PlayerData.h"

class Game
{
	public: 
		Game(int playerCount);
		void Update();
		bool End() { return endGame; }

	private:
		void Build();
		void Trade();
		void Move();
		void HandleMovementResult();
		
		DiceHandler diceHandler;
		bool endGame;
		std::vector<PlayerData> players;
		int playerTurnIndex;
};

