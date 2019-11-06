#pragma once
#include <stdlib.h>
#include <time.h>

class DiceHandler
{
	public:
		DiceHandler() { srand(time(NULL)); }
		DiceHandler(int seed);
		int RollDice();
		bool GetIsDouble() { return isDouble; }

	private:
		int RollDie();
		bool isDouble = false;
};

