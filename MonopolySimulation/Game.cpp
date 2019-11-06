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

void Game::HandleMovementResult()
{
}

void Game::Sell()
{
}


