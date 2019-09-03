#pragma once
#include <stdlib.h>
#include <time.h>

class DiceHandler
{
	public:
		DiceHandler(int seed);
		int RollDice();
		bool GetIsDouble() { return isDouble; }

	private:
		int RollDie();
		bool isDouble;
};

