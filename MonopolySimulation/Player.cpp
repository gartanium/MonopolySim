#include "Player.h"


/*
	everything the player needs to receive the property
	subtracting the cost from cash
	updating assets
	and receive property

	can probably be modified by adding an int in the call to allow use for trading
*/
void Player::ReceiveProperty(Property &property, int playerTurnIndex)
{
	playerData.SpendCash(property.GetCost());
	playerData.updateLiquidAssets(property.GetMorgagePrice());
	property.setOwner(playerTurnIndex);
}

/*
	sets the players status to in jail
	and moves them to the jail location
*/
void Player::sendToJail()
{
	playerData.setInJailStatus(true);
	playerData.SetPosition(10);
	timesRolledDoubles = 0;
}
/*
	adds time to the player being in jail if the plyaer is already in jail
	the player no longer becomes in jail if three turns has passed/on the third turn the player
	is released from jail. if the player rolls doubles it will reset jail time and automatically
	release them from jail
*/
void Player::AddTimeInJail(bool doubles)
{
	if (playerData.IsInJail() && !doubles)
	{
		int jailTime = playerData.getJailTime();
		jailTime++;
		playerData.setJailTime(jailTime);
		if (jailTime == 3)
		{
			PayBail(50);
		}

	}
	else
	{
		PayBail(0);
	}
	
}

void Player::PayBail(int bail)
{
	playerData.SpendCash(bail);
	playerData.setInJailStatus(false);
	playerData.setJailTime(0);
}

void Player::payRent(Property property, int payMod)
{
	playerData.SpendCash(property.GetCurrentRent() * payMod);
	playerData.updateAssets();
}

void Player::receiveRent(Property property, int payMod)
{
	playerData.ReceiveCash(property.GetCurrentRent() * payMod);
}

void Player::payTaxes(int taxes)
{
	 playerData.SpendCash(taxes);
}

void Player::Die()
{
	playerData.SpendCash((playerData.GetCash()+ 3000));
	playerData.updateLiquidAssets(-(playerData.getLiquidAssets()+ 1000));

}


void Player::Execute(Player deadPlayer)
{
	int tempAssets = deadPlayer.getAssets();
	int tempCash = deadPlayer.getCash();

	this->playerData.ReceiveCash(tempCash);
	this->playerData.updateLiquidAssets(deadPlayer.getAssets() - tempCash);
}

void Player::mortgageProperty(Property property)
{
	property.setMortgaged(true);
	playerData.ReceiveCash(property.GetMorgagePrice());
}



/*
	moves the player a specified amount.
	considers jail time and if they get out of jail
	in that turn or not
	handles moving past go
*/
void Player::Move(int value, bool doubles)
{
	int position = playerData.GetPosition();
	AddTimeInJail(doubles);
	if (doubles)
	{
		timesRolledDoubles++;
	}
	else
	{
		timesRolledDoubles = 0;
	}
	if (timesRolledDoubles == 3)
	{
		sendToJail();
	}
	
	if (!playerData.IsInJail())
	{
		playerData.SetPosition(position += value); 
		if (playerData.GetPosition() > 39 || playerData.GetPosition() == 0)
		{
			playerData.ReceiveCash(200);
			playerData.formatPosition();

		}
	}
	
	
}


