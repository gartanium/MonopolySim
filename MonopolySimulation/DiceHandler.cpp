#include "DiceHandler.h"

DiceHandler::DiceHandler(int seed) 
{ 
	srand(seed); 
}

int DiceHandler::RollDice()
{
	int dieOne = RollDie();
	int dieTwo = RollDie();
	
	isDouble = dieOne == dieTwo;
	
	return dieOne + dieTwo;
}

int DiceHandler::RollDie()
{
	int randomDieRoll1 = rand() % 6 + 1;
	return randomDieRoll1;
}
