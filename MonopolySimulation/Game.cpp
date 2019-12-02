#include "Game.h"

Game::Game(int playerCount)
{
	srand(time(0));
	playerTurnIndex = 0;
	endGame = false;
	for (int i = 0; i < playerCount; i++) 
	{
		Player newPlayer;
		players.push_back(newPlayer);
	}


	for (int i = 0; i < 17; i++)
	{
		communityChest.push_back(i + 1);
	}
	
	for (int i = 0; i < 17; i++)
	{
		std::swap(communityChest[i], communityChest[(rand() % 16 + 0)]);
	}
	
	for (int i = 0; i < 18; i++)
	{
		chance.push_back(i + 1);
	}

	for (int i = 0; i < 18; i++)
	{
		std::swap(chance[i], chance[(rand() % 17 + 0)]);
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
		----pays taxes

*/
void Game::HandleMovementResult(int payMod)
{
	int playerLocation = players[playerTurnIndex].GetPosition();
	//landing on income tax
	if (playerLocation == 4)
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
	// landing on luxurty tax
	else if (playerLocation == 38)
	{
		players[playerTurnIndex].payTaxes(75);
	}
	// landing on go to jail
	else if (playerLocation == 30)
	{
		players[playerTurnIndex].sendToJail();
	}
	//landing on a chance
	else if (playerLocation == 7 || playerLocation == 22 || playerLocation == 36)
	{
		Chance(chance.back());

	}
	//landing on a community chest
	else if (playerLocation == 2 || playerLocation == 17 || playerLocation == 33)
	{
		CommunityChest(communityChest.back());

	}
	//landing on a property
	else
	{
		//landing on a property
		for (PropertyIt = Deeds.begin(); PropertyIt != Deeds.end(); ++PropertyIt)
		{
			//if the property landed on is unowned	
			if (PropertyIt->GetPosition() == playerLocation && PropertyIt->getOwnerNumber() == -1)
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

			//if the property is owned
			else if (PropertyIt->GetPosition() == playerLocation &&
					PropertyIt->getOwnerNumber() >= 0 &&
					PropertyIt->getOwnerNumber() != playerTurnIndex)
				 {
					int owner = PropertyIt->getOwnerNumber();

					
					
					//if the property is mortgaged
					if (PropertyIt->Mortgaged())
					{

					}
					// if a player has less assets than the rent make them go bankrupt
					else if (players[playerTurnIndex].getAssets() < (PropertyIt->GetCurrentRent() * payMod))
					{
						//all the players property and money goes to the owner
						executePlayer(owner);

					}
					// if the player has enough money on hand fork it over
					else if (players[playerTurnIndex].getCash() > (PropertyIt->GetCurrentRent()* payMod))
					{
						players[owner].receiveRent(*PropertyIt, payMod);
							players[playerTurnIndex].payRent(*PropertyIt, payMod);
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
	for (PropertyIt = Deeds.begin(); PropertyIt != Deeds.end(); ++PropertyIt)
	{
		if (PropertyIt->getOwnerNumber() == playerTurnIndex)
		{
			PropertyIt->setOwner(owner);
		}
	} 

}

void Game::Chance(int chanceCard)
{
	int location = players[playerTurnIndex].GetPosition();
	switch (chanceCard)
	{
		//advance to go
	case 1:
		players[playerTurnIndex].Move(-location, false);
		break;
		//advance to illinois ave
	case 2:
		//passes go if got at location 36
		if (location == 36)
		{
			players[playerTurnIndex].receiveMoney(200);
		}
		players[playerTurnIndex].Move((-location + 24), false);
		HandleMovementResult(1);
		break;
		//advance to st charles place
	case 3:
		// passes go if at location 36 or 22
		if (location == 36 || location == 22)
		{
			players[playerTurnIndex].receiveMoney(200);
		}
		players[playerTurnIndex].Move((-location + 11), false);
		HandleMovementResult(1);
		break;
		//advance token to nearest utility if owned throw dice and pay owner 10x roll
	case 4:
		if (location == 7)
		{
			players[playerTurnIndex].Move(5, false);
			HandleMovementResult(10);
		}
		else
		{
			players[playerTurnIndex].Move((-location + 28), false);
			HandleMovementResult(10);
		}
		break;
		//advance to nearest railroad if owned pay twice the rent
	case 5:
		if (location == 7)
		{
			players[playerTurnIndex].Move(-2, false);
			HandleMovementResult(2);
		}
		else if (location == 22)
		{
			players[playerTurnIndex].Move(3, false);
			HandleMovementResult(2);
		}
		else
		{
			players[playerTurnIndex].Move(-1, false);
			HandleMovementResult(2);
		}
	
		break;
		//bank pays dividend of $50
	case 6:
		players[playerTurnIndex].receiveMoney(50);
		break;
		//get out of jail free card
	case 7:
		players[playerTurnIndex].setGOOJF(true);
		break;
		//go back three spaces
	case 8:
		players[playerTurnIndex].Move((location - 3), false);
		HandleMovementResult(1);
		break;
		//go to jail
	case 9:
		players[playerTurnIndex].sendToJail();
		break;
		//make general repairs on houses $25 per house $100 per hotel
	case 10:
		StreetRepairs(25,100);
		break;
		//won crossword collect $100
	case 11:
		players[playerTurnIndex].receiveMoney(100);
		break;
		//pay poor tax of $15
	case 12:
		players[playerTurnIndex].spendMoney(15);
		break;
		//trip to reading railroad. will always pass go so collect $200
	case 13:
		players[playerTurnIndex].Move((-location + 5), false);
		players[playerTurnIndex].receiveMoney(200);
		HandleMovementResult(1);
		break;
		//take a walk on the boardwalk
	case 14:
		players[playerTurnIndex].Move((-location + 39), false);
		HandleMovementResult(1);

		break;
		// elected chairman pay each player $50
	case 15:
		for (int i = 0; i < players.size(); i++)
		{
			players[playerTurnIndex].spendMoney(50);
			players[i].receiveMoney(50);
		}
		break;
		//building loan matures collect $150
	case 16:
		players[playerTurnIndex].receiveMoney(150);
		break;

	default:
		break;
	}
	chance.push_front(chance.back());
	chance.pop_back();
}

void Game::StreetRepairs(int houseCost, int hotelCost)
{
	int houseCount = 0;
	int hotelCount = 0;
	for (PropertyIt = Deeds.begin(); PropertyIt != Deeds.end(); ++PropertyIt)
	{
		if (PropertyIt->getOwnerNumber() == playerTurnIndex)
		{
			if (PropertyIt->GetHouseCount() == 5)
			{
				hotelCount++;
			}
			else
			{
				houseCount += PropertyIt->GetHouseCount();
			}
		}
	}
	int repairCost = ((houseCount * houseCost) + (hotelCount * hotelCost));
	players[playerTurnIndex].spendMoney(repairCost);
}


void Game::CommunityChest(int communityChestCard)
{
	int location = players[playerTurnIndex].GetPosition();
	switch (communityChestCard)
	{
		//advance to go
	case 1:
		players[playerTurnIndex].Move(-location, false);
		break;
		//bank error in favor collect $200
	case 2:
		players[playerTurnIndex].receiveMoney(200);
		break;
		//Doctors fee pay $50
	case 3:
		players[playerTurnIndex].spendMoney(50);
		break;
		// from sale get $50
	case 4:
		players[playerTurnIndex].receiveMoney(50);
		break;
		//get out of fail free card
	case 5:
		players[playerTurnIndex].setGOOJF(true);
		break;
		// go to jail
	case 6:
		players[playerTurnIndex].sendToJail();
		break;
	//grand opera night $50 from reach player
	case 7:
	{
		for (int i = 0; i < players.size(); i++)
		{
			players[i].spendMoney(50);
			players[playerTurnIndex].receiveMoney(50);
		}	
	}
		break;
	//holiday fund matures collect $100
	case 8:
		players[playerTurnIndex].receiveMoney(100);

		break;
	//income tax refund collect $20
	case 9:
		players[playerTurnIndex].receiveMoney(20);
		break;
	//it is your birthday collect $10
	case 10:
		players[playerTurnIndex].receiveMoney(10);
		break;
		//life insurance matures collect $100
	case 11:
		players[playerTurnIndex].receiveMoney(100);

		break;
		//pay hospital fees of $100
	case 12:
		players[playerTurnIndex].spendMoney(100);
		break;
		//pay school fees of $150
	case 13:
		players[playerTurnIndex].spendMoney(150);
		break;

		//receive $25 consultancy fee
	case 14:
		players[playerTurnIndex].receiveMoney(25);
		break;
		//assessed for street repairs $40 per house $115 per hotel
	case 15:
		StreetRepairs(40, 115);
		break;
		// won second place in beauty contest collect $10
	case 16:
		players[playerTurnIndex].receiveMoney(10);
		break;
		//inherit $100
	case 17:
		players[playerTurnIndex].receiveMoney(100);
		break;
	default:
		break;
	}
	communityChest.push_front(communityChest.back());
	communityChest.pop_back();
}

