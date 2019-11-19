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
	//landing on income tax
	if (players[playerTurnIndex].GetPosition() == 4)
	{
		/*server needs to ask player if they want to pay $200 or 10%
		*
		*   SERVER ACTION REQUIRED
		*
		*
		*
		*/
		//if (playerResponse == 0)
		//{
		//	players[playerTurnIndex].payTaxes(200);
		/*}
		else
		{
			*/
			players[playerTurnIndex].payTaxes((players[playerTurnIndex].getAssets()) * .1);
		//}
		
		
	}
	else if (players[playerTurnIndex].GetPosition() == 38)
	{
		players[playerTurnIndex].payTaxes(75);
	}
	else if (players[playerTurnIndex].GetPosition() == 30)
	{
		players[playerTurnIndex].sendToJail();
	}
	else
	{
		//landing on a property
		for (std::vector<Property>::iterator it = Deeds.begin(); it != Deeds.end(); ++it)
		{
			//if the property landed on is unowned	
			if (it->GetPosition() == players[playerTurnIndex].GetPosition() && it->getOwnerNumber() == -1)
			{
				// server will ask if the player wants to buy the property
				/*
				*
				*
				*SERVER ACTION REQUIRED
				*
				*
				*/
				// players[playerTurnIndex].ReceiveProperty(*it);
				break;
			}
			// if the property is owned, this includes if the owner lands on his own
			// property, essentially the owner will "pay himself"
			else if (it->GetPosition() == players[playerTurnIndex].GetPosition() && 
					it->getOwnerNumber() >= 0 && 
					it->getOwnerNumber() != playerTurnIndex)
				 {
					int owner = it->getOwnerNumber();
					// if a player has less assets than the rent make them go bankrupt
					if (players[playerTurnIndex].getAssets() < it->GetCurrentRent())
					{
						//all the players property and money goes to the owner
						executePlayer(owner);

					}
					// if the player has enough money on hand fork it over
					else if (players[playerTurnIndex].getCash() > it->GetCurrentRent())
					{
						players[owner].receiveRent(*it);
							players[playerTurnIndex].payRent(*it);
					}
					// if the player does not have enough cash on hand the player
					// has to sell,mortgage things until they do
					else
					{
						/*
						*
						*
						*SERVER ACTION REQUIRED
						*
						*
						*/

					}

					break;
			
				 }
		}

	}

	
	

}

void Game::Sell()
{
}


/*
	takes away all the money assets and properties from one player to another
	also sets the assets of the "dead" player to negative just in case
*/
void Game::executePlayer(int owner)
{
	players[owner].Execute(players[playerTurnIndex]);
	players[playerTurnIndex].Die();
	for (std::vector<Property>::iterator it = Deeds.begin(); it != Deeds.end(); ++it)
	{
		if (it->getOwnerNumber() == playerTurnIndex)
		{
			it->setOwner(owner);
		}
	} 

}


