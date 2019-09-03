#include "Game.h"

Game::Game(int playerCount)
{
	playerTurnIndex = 0;
	endGame = false;
	for (int i = 0; i < playerCount; i++) 
	{
		PlayerData newPlayer;
		players.push_back(newPlayer);
	}
}

void Game::Update()
{
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
	players[playerTurnIndex].Move(diceRoll);
}

void Game::HandleMovementResult()
{
}


