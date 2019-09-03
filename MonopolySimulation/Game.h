#pragma once
#include "DiceHandler.h"

class Game
{
	public: 
		Game() { endGame = false; }
		void Update();
		bool End() { return endGame; }

	private:
		void Build();
		void Trade();
		void Move();
		void HandleMovementResult();
		DiceHandler diceHandler;
		bool endGame;
};

