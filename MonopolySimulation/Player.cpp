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
	playerData.updateAssets();

}

/*
	sets the players status to in jail
	and moves them to the jail location
*/
void Player::sendToJail()
{
	playerData.setInJailStatus(true);
	playerData.SetPosition(10);
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
			playerData.updateAssets();
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

void Player::payRent(Property property)
{
	playerData.SpendCash(property.GetCurrentRent());
	playerData.updateAssets();
}

void Player::receiveRent(Property property)
{
	playerData.ReceiveCash(property.GetCurrentRent());
	playerData.updateAssets();
}

void Player::payTaxes(int taxes)
{
	 playerData.SpendCash(taxes);
	 playerData.updateAssets();
}

void Player::Die()
{
	playerData.SpendCash((playerData.GetCash()+ 3000));
	playerData.updateLiquidAssets(-(playerData.getLiquidAssets()+ 1000));
	playerData.updateAssets();

}


void Player::Execute(Player deadPlayer)
{
	int tempAssets = deadPlayer.getAssets();
	int tempCash = deadPlayer.getCash();

	this->playerData.ReceiveCash(tempCash);
	this->playerData.updateLiquidAssets(deadPlayer.getAssets() - tempCash);
	this->playerData.updateAssets();
}



/*
	moves the player a specified amount.
	considers jail time and if they get out of jail
	in that turn or not
	needs to consider if the user has rolled doubles a third time 
	to see whether or not the player needs to go to jail
*/
void Player::Move(int value, bool doubles)
{
	int position = playerData.GetPosition();
	AddTimeInJail(doubles);
	if (!playerData.IsInJail())
	{
		playerData.SetPosition(position += value); 
	}
	
	
}


