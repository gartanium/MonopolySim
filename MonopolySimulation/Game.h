#pragma once
#include <iostream>
#include <algorithm>
#include "DiceHandler.h"
#include <vector>
#include "Player.h"
#include <deque>
#include <time.h>

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
		void HandleMovementResult(int payModifier);
		void Sell();
		void NextPlayer() { playerTurnIndex++; };
		void executePlayer(int owner);

		void Chance(int chanceCard);
		void CommunityChest(int communityC);

		void StreetRepairs(int houseCost, int hotelCost);
		
		DiceHandler diceHandler;
		bool endGame;
		std::vector<Player> players;
		std::vector<Property>::iterator PropertyIt;

		// this is the current player
		int playerTurnIndex;
		std::vector<Property>Deeds;
		std::deque<int>communityChest;
		std::deque<int>chance;
};

