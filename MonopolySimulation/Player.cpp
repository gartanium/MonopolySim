#include "Player.h"


/*
	everything the player needs to receive the property
	subtracting the cost from cash
	updating assets
	and receive property
*/
void Player::ReceiveProperty(Property property)
{
	playerData.SpendCash(property.GetCost());
	playerData.updateAssets(property.GetMorgagePrice());

}

/*
	sets the players status to in jail
*/
void Player::sendToJail()
{
	playerData.setInJailStatus(true);
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


