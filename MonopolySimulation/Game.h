#pragma once
#include "DiceHandler.h"

class Game
{
	public: 
		void Update();

	private:
		void Build();
		void Trade();
		void Move();
		void HandleMovementResult();
		DiceHandler diceHandler;
};

