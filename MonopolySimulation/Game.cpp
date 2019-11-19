#include "Game.h"

Game::Game(int playerCount)
{
	playerTurnIndex = 0;
	endGame = false;
	for (int i = 0; i < playerCount; i++) 
	{
		Player newPlayer;
		players.push_back(newPlayer);
	}
}

void Game::Update()
{
	(playerTurnIndex + 1) % players.size();
	
	
}

void Game::Build()
{
}

void Game::Trade()
{
}

void Game::Move()
{	
	int diceRoll = diceHandler.RollDice();
	bool doubles = diceHandler.GetIsDouble();
	players[playerTurnIndex].Move(diceRoll, doubles);
}


/*
		handles the  result of the movement. 
		----asks if the player wants to buy
			unowned property
		----sends the player to jail
		----makes the player pay rent to
			the property owner
		----draws a chance or community chest card

*/
void Game::HandleMovementResult()
{

	for (std::vector<Property>::iterator it = Deeds.begin(); it != Deeds.end(); ++it)
	{
		//if the property landed on is unowned	
		if (it->GetPosition() == players[playerTurnIndex].GetPosition() && it->getOwnerNumber() == -1)
		{
			// server will ask if the player wants to buy the property
			// players[playerTurnIndex].ReceiveProperty(*it);
			break;
		}
		// if the property is owned, this includes if the owner lands on his own
		// property, essentially the owner will "pay himself"
		else if (it->GetPosition() == players[playerTurnIndex].GetPosition() && it->getOwnerNumber() >= 0)
		{
			int owner = it->getOwnerNumber();
			players[owner].receiveRent(*it);
			players[playerTurnIndex].payRent(*it);
			break;
		}

	}
	

}

void Game::Sell()
{
}


