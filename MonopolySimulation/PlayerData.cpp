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



int* PlayerData::GetSpecialCards()
{
	return nullptr;
}




bool PlayerData::IsBankrupt()
{
	if (assets <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

/*
	sets the status of the player to in jail or not in jail
	if going to jail it also moves them to jail
*/
void PlayerData::setInJailStatus(bool isInJail)
{
	if (IsInJail)
	{
		this->isInJail = isInJail;
		position = 10;
	}
	else
	{
		this->isInJail = isInJail;
	}
	
}



std::string PlayerData::Serialize()
{
	return std::string();
}


