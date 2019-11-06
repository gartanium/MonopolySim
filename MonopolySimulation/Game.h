#pragma once
#include "DiceHandler.h"
#include <vector>
#include "Player.h"

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
		void Sell();
		void NextPlayer() { playerTurnIndex++; };
		
		DiceHandler diceHandler;
		bool endGame;
		std::vector<Player> players;
		int playerTurnIndex;
};

