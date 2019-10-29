#include "PlayerData.h"

int PlayerData::GetPosition()
{
	return position % 40;
}

int* PlayerData::GetUnmorgaged()
{
	return nullptr;
}

int* PlayerData::GetMorgaged()
{
	return nullptr;
}

int* PlayerData::GetCash()
{
	return nullptr;
}

int* PlayerData::GetSpecialCards()
{
	return nullptr;
}

/*
	Returns how long the player has been in jail so the server knows when they need to pay to get out
*/
int PlayerData::GetTimeInJail()
{
	return jailTime;
}

bool PlayerData::IsInJail()
{
	return isInJail;
}

int PlayerData::SpendCash(int value)
{
	return 0;
}

int PlayerData::ReceiveCash(int value)
{
	return 0;
}

bool PlayerData::IsBankrupt()
{
	return false;
}

void PlayerData::ReceiveProperty(Property)
{
}

void PlayerData::sendToJail()
{
	isInJail = true;
}

/*
	adds time to the player being in jail if the plyaer is already in jail
	the player no longer becomes in jail if three turns has passed/on the third turn the player
	is released from jail
*/
void PlayerData::AddTimeInJail()
{
	if (isInJail)
	{
		jailTime++;
		if (jailTime == 3)
		{
			isInJail = false;
			jailTime = 0;
			//this is probably where money should be subtracted for getting out of jail

		}

	}
	
}

std::string PlayerData::Serialize()
{
	return std::string();
}

void PlayerData::Move(int value)
{
	
	AddTimeInJail();
	if (!isInJail)
	{
		position += value;
	}
	
	
}
