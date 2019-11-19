#pragma once
#include <iostream>
#include "DiceHandler.h"
#include <vector>
#include "Player.h"

class Game
{
	public: 
		Game(int playerCount);
		void Update();
		bool End() { return endGame; }

	//private:
		void Build();
		void Trade();
		void Move();
		void HandleMovementResult();
		void Sell();
		void NextPlayer() { playerTurnIndex++; };
		void executePlayer(int owner);
		
		DiceHandler diceHandler;
		bool endGame;
		std::vector<Player> players;

		// this is the current player
		int playerTurnIndex;
		std::vector<Property>Deeds;
};

