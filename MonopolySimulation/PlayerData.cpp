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

int* PlayerData::GetTimeInJail()
{
	return nullptr;
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

std::string PlayerData::Serialize()
{
	return std::string();
}

void PlayerData::Move(int value)
{
	position += value;
}
